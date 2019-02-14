#ifndef BE_DEBUG_H
#define BE_DEBUG_H

#include "be_object.h"

void be_dprintcode(bclosure *cl);
void be_debug_error(bvm *vm, int errcode, const char *msg);
void be_debug_ins_info(bvm *vm);

#endif
