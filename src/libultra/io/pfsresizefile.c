/*
 * libultra io/pfsresizefile.c: osPfsReSizeFile, which changes the size of
 * an existing game note.  The SDK's function reference says it was removed
 * from the OS in 2.0I, so decompals/ultralib has no source for it; this
 * is decompiled from the game, in the style of the 2.0I (pre-2.0J)
 * osPfsAllocateFile and osPfsDeleteFile it is built from, -O1 like the
 * rest of io/.
 *
 * Growing a note declares new pages bank by bank (__osPfsDeclearPage) and
 * links them after the note's last page; shrinking it walks the note to
 * the new last page, ends the chain there and releases the rest
 * (__osPfsReleasePages), adjusting the directory entry's data_sum.
 */
#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"

#define ROUND_UP_DIVIDE(numerator, denominator) (((numerator) + (denominator)-1) / (denominator))

s32 osPfsReSizeFile(OSPfs* pfs, u16 company_code, u32 game_code, u8* game_name, u8* ext_name, int length_in_bytes) {
    int start_page;
    s32 ret = 0;
    int file_size_in_pages;
    __OSInode inode;
    __OSInode backup_inode;
    __OSDir dir;
    s32 file_no;
    int pages;
    __OSInodeUnit old_page;
    __OSInodeUnit next_page;
    u16 sum = 0;
    s32 bytes;
    int new_pages;
    u8 bank;
    int decleared;
    int firsttime = 0;
    int linked = 0;
    int j;
    __OSInodeUnit last_page;
    int last_page_no;
    int old_last_page = 0;
    u8 old_bank = 0;
    u8 last_bank = 0;
    int bank_changes = 0;
    __OSInodeUnit page;
    int offset;

    if (company_code == 0 || game_code == 0) {
        return PFS_ERR_INVALID;
    }

    file_size_in_pages = ROUND_UP_DIVIDE(length_in_bytes, BLOCKSIZE * PFS_ONE_PAGE);

    if ((pfs->status & PFS_INITIALIZED) == FALSE) {
        return PFS_ERR_INVALID;
    }

    PFS_CHECK_ID();

    if (((ret = osPfsFindFile(pfs, company_code, game_code, game_name, ext_name, &file_no)) != 0) &&
        ret != PFS_ERR_INVALID) {
        return ret;
    }

    if (file_no == -1) {
        return PFS_ERR_INVALID;
    }

    if (file_size_in_pages != 0) {
        SET_ACTIVEBANK_TO_ZERO();
        ERRCK(__osContRamRead(pfs->queue, pfs->channel, pfs->dir_table + file_no, (u8*)&dir));

        if (dir.start_page.ipage < pfs->inode_start_page) {
            return PFS_ERR_INCONSISTENT;
        }

        // count the note's pages, and find its last one
        pages = 0;
        start_page = dir.start_page.inode_t.page;
        old_last_page = dir.start_page.inode_t.page;

        for (bank = dir.start_page.inode_t.bank; bank < pfs->banks;) {
            ERRCK(__osPfsRWInode(pfs, &inode, PFS_READ, bank));
            next_page = inode.inode_page[start_page];

            while (next_page.ipage >= pfs->inode_start_page) {
                pages++;
                old_last_page = next_page.inode_t.page;
                next_page = inode.inode_page[next_page.inode_t.page];

                if (next_page.inode_t.bank != bank) {
                    bank = next_page.inode_t.bank;
                    start_page = next_page.inode_t.page;
                    old_last_page = next_page.inode_t.page;
                    break;
                }
            }

            if (next_page.ipage == PFS_EOF) {
                pages++;
                break;
            }
        }

        last_bank = bank;

        if (bank >= pfs->banks) {
            return PFS_ERR_INCONSISTENT;
        }

        if (file_size_in_pages > pages) {
            new_pages = file_size_in_pages - pages;
            ret = osPfsFreeBlocks(pfs, &bytes);

            if (new_pages > bytes / (BLOCKSIZE * PFS_ONE_PAGE)) {
                return PFS_DATA_FULL;
            }

            old_bank = bank;
            for (j = 0; j < ARRLEN(inode.inode_page); j++) {
                backup_inode.inode_page[j].ipage = inode.inode_page[j].ipage;
            }

            for (bank = 0; bank < pfs->banks; bank++) {
                ERRCK(__osPfsRWInode(pfs, &inode, PFS_READ, bank));
                ERRCK(__osPfsDeclearPage(pfs, &inode, new_pages, &start_page, bank, &decleared, &last_page_no));

                if (start_page != -1) {
                    if (firsttime != 0 || last_bank != bank) {
                        linked++;
                        backup_inode.inode_page[old_last_page].inode_t.bank = bank;
                        backup_inode.inode_page[old_last_page].inode_t.page = start_page;
                        ERRCK(__osPfsRWInode(pfs, &backup_inode, PFS_WRITE, old_bank));
                    }

                    for (j = 0; j < ARRLEN(inode.inode_page); j++) {
                        backup_inode.inode_page[j].ipage = inode.inode_page[j].ipage;
                    }

                    if (new_pages > decleared) {
                        new_pages -= decleared;
                    } else {
                        new_pages = 0;
                        old_bank = bank;
                        break;
                    }

                    old_last_page = last_page_no;
                    old_bank = bank;
                    firsttime++;
                }
            }

            if (new_pages > 0 || start_page == -1) {
                return PFS_ERR_INCONSISTENT;
            }

            if (linked == 0) {
                backup_inode.inode_page[old_last_page].inode_t.bank = bank;
                backup_inode.inode_page[old_last_page].inode_t.page = start_page;
            }

            ERRCK(__osPfsRWInode(pfs, &backup_inode, PFS_WRITE, old_bank));
        } else if (file_size_in_pages < pages) {
            page = dir.start_page;

            for (bank = dir.start_page.inode_t.bank; bank < pfs->banks;) {
                ERRCK(__osPfsRWInode(pfs, &inode, PFS_READ, bank));
                old_page = page;
                next_page = inode.inode_page[page.inode_t.page];
                file_size_in_pages--;
                offset = (bank > 0) ? 1 : pfs->inode_start_page;

                if (next_page.inode_t.page < offset && next_page.ipage != PFS_EOF) {
                    return PFS_ERR_INCONSISTENT;
                }

                while (file_size_in_pages > 0 && next_page.ipage >= pfs->inode_start_page) {
                    file_size_in_pages--;
                    old_page = next_page;
                    next_page = inode.inode_page[next_page.inode_t.page];

                    if (next_page.inode_t.bank != bank) {
                        if (file_size_in_pages == 1) {
                            inode.inode_page[old_page.inode_t.page].ipage = PFS_EOF;
                            ERRCK(__osPfsRWInode(pfs, &inode, PFS_WRITE, bank));
                        }
                        bank_changes++;
                        page = next_page;
                        ERRCK(__osPfsRWInode(pfs, &inode, PFS_READ, bank = next_page.inode_t.bank));
                        break;
                    }
                }

                if (file_size_in_pages == 0) {
                    break;
                }
            }

            if (bank >= pfs->banks) {
                return PFS_ERR_INCONSISTENT;
            }

            if (bank_changes == 0) {
                inode.inode_page[old_page.inode_t.page].ipage = PFS_EOF;
            } else {
                inode.inode_page[next_page.inode_t.page].ipage = PFS_EOF;
            }

            if (next_page.ipage == PFS_EOF) {
                inode.inode_page[old_page.inode_t.page].ipage = PFS_PAGE_NOT_USED;
                ERRCK(__osPfsRWInode(pfs, &inode, PFS_WRITE, bank));
            } else {
                page = next_page;

                for (bank = next_page.inode_t.bank; bank < pfs->banks;) {
                    ERRCK(__osPfsReleasePages(pfs, &inode, page.inode_t.page, &sum, bank, &last_page, FALSE));
                    ERRCK(__osPfsRWInode(pfs, &inode, PFS_WRITE, bank));

                    if (last_page.ipage == PFS_EOF) {
                        break;
                    }

                    bank = last_page.inode_t.bank;
                    page = last_page;
                    ERRCK(__osPfsRWInode(pfs, &inode, PFS_READ, bank));
                }

                if (bank >= pfs->banks) {
                    return PFS_ERR_INCONSISTENT;
                }
            }

            if (dir.data_sum > sum) {
                dir.data_sum -= sum;
            } else {
                dir.data_sum = sum - dir.data_sum;
            }

            ERRCK(__osContRamWrite(pfs->queue, pfs->channel, pfs->dir_table + file_no, (u8*)&dir, FALSE));
        }

        return ret;
    } else {
        return PFS_ERR_INVALID;
    }
}
