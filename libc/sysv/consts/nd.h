#ifndef COSMOPOLITAN_LIBC_SYSV_CONSTS_ND_H_
#define COSMOPOLITAN_LIBC_SYSV_CONSTS_ND_H_
#include "libc/runtime/symbolic.h"

#define ND_NA_FLAG_OVERRIDE SYMBOLIC(ND_NA_FLAG_OVERRIDE)
#define ND_NA_FLAG_ROUTER SYMBOLIC(ND_NA_FLAG_ROUTER)
#define ND_NA_FLAG_SOLICITED SYMBOLIC(ND_NA_FLAG_SOLICITED)
#define ND_NEIGHBOR_ADVERT SYMBOLIC(ND_NEIGHBOR_ADVERT)
#define ND_NEIGHBOR_SOLICIT SYMBOLIC(ND_NEIGHBOR_SOLICIT)
#define ND_RA_FLAG_HOME_AGENT SYMBOLIC(ND_RA_FLAG_HOME_AGENT)
#define ND_RA_FLAG_MANAGED SYMBOLIC(ND_RA_FLAG_MANAGED)
#define ND_RA_FLAG_OTHER SYMBOLIC(ND_RA_FLAG_OTHER)
#define ND_REDIRECT SYMBOLIC(ND_REDIRECT)
#define ND_ROUTER_ADVERT SYMBOLIC(ND_ROUTER_ADVERT)
#define ND_ROUTER_SOLICIT SYMBOLIC(ND_ROUTER_SOLICIT)

#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

hidden extern const long ND_NA_FLAG_OVERRIDE;
hidden extern const long ND_NA_FLAG_ROUTER;
hidden extern const long ND_NA_FLAG_SOLICITED;
hidden extern const long ND_NEIGHBOR_ADVERT;
hidden extern const long ND_NEIGHBOR_SOLICIT;
hidden extern const long ND_RA_FLAG_HOME_AGENT;
hidden extern const long ND_RA_FLAG_MANAGED;
hidden extern const long ND_RA_FLAG_OTHER;
hidden extern const long ND_REDIRECT;
hidden extern const long ND_ROUTER_ADVERT;
hidden extern const long ND_ROUTER_SOLICIT;

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_SYSV_CONSTS_ND_H_ */
