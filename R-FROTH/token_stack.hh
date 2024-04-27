// token_stack.hh
// This header ensures C linkage is enforced when running C++ unit tessts on C code.

#include <math.h>

#ifdef __cplusplus

extern "C" {
#include "token_stack.h"
}

#else

#include "token_stack.h"

#endif
