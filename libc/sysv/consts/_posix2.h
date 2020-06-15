#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS__POSIX2_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS__POSIX2_H_
#include "libc/runtime/symbolic.h"

#define _POSIX2_BC_BASE_MAX SYMBOLIC(_POSIX2_BC_BASE_MAX)
#define _POSIX2_BC_DIM_MAX SYMBOLIC(_POSIX2_BC_DIM_MAX)
#define _POSIX2_BC_SCALE_MAX SYMBOLIC(_POSIX2_BC_SCALE_MAX)
#define _POSIX2_BC_STRING_MAX SYMBOLIC(_POSIX2_BC_STRING_MAX)
#define _POSIX2_CHARCLASS_NAME_MAX SYMBOLIC(_POSIX2_CHARCLASS_NAME_MAX)
#define _POSIX2_COLL_WEIGHTS_MAX SYMBOLIC(_POSIX2_COLL_WEIGHTS_MAX)
#define _POSIX2_C_BIND SYMBOLIC(_POSIX2_C_BIND)
#define _POSIX2_EXPR_NEST_MAX SYMBOLIC(_POSIX2_EXPR_NEST_MAX)
#define _POSIX2_LINE_MAX SYMBOLIC(_POSIX2_LINE_MAX)
#define _POSIX2_RE_DUP_MAX SYMBOLIC(_POSIX2_RE_DUP_MAX)
#define _POSIX2_VERSION SYMBOLIC(_POSIX2_VERSION)

#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

hidden extern const long _POSIX2_BC_BASE_MAX;
hidden extern const long _POSIX2_BC_DIM_MAX;
hidden extern const long _POSIX2_BC_SCALE_MAX;
hidden extern const long _POSIX2_BC_STRING_MAX;
hidden extern const long _POSIX2_CHARCLASS_NAME_MAX;
hidden extern const long _POSIX2_COLL_WEIGHTS_MAX;
hidden extern const long _POSIX2_C_BIND;
hidden extern const long _POSIX2_EXPR_NEST_MAX;
hidden extern const long _POSIX2_LINE_MAX;
hidden extern const long _POSIX2_RE_DUP_MAX;
hidden extern const long _POSIX2_VERSION;

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS__POSIX2_H_ */
