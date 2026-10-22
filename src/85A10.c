#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/85A10/func_8026B210.s")

#pragma GLOBAL_ASM("asm/nonmatchings/85A10/func_8026B228.s")

#pragma GLOBAL_ASM("asm/nonmatchings/85A10/func_8026B238.s")

#pragma GLOBAL_ASM("asm/nonmatchings/85A10/func_8026B584.s")

#pragma GLOBAL_ASM("asm/nonmatchings/85A10/func_8026B72C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/85A10/func_8026B79C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/85A10/func_8026B7A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/85A10/func_8026B7D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/85A10/func_8026B804.s")

/* jp's code differs (docs/DECOMPILING.md, "Versions"): each version's
   extract writes its own func_8026B9CC.s, and tools/version_ifs.py keeps
   asm-processor from seeing the line of the other. */
#if VERSION_JP
#pragma GLOBAL_ASM("asm/nonmatchings/85A10/func_8026B9CC.s")
#else
#pragma GLOBAL_ASM("asm/nonmatchings/85A10/func_8026B9CC.s")
#endif
