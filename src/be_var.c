#include "be_var.h"
#include "be_vm.h"
#include "be_vector.h"
#include "be_string.h"
#include "be_map.h"
#include "be_gc.h"

void be_globalvar_init(bvm *vm)
{
    vm->gbldesc.idxtab = be_map_new(vm);
    vm->gbldesc.nglobal = 0;
    be_vector_init(&vm->gbldesc.gvalist, sizeof(bvalue));
    be_gc_fix(vm, gc_object(vm->gbldesc.idxtab));
}

void be_globalvar_deinit(bvm *vm)
{
    vm->gbldesc.idxtab = NULL;
    vm->gbldesc.nglobal = 0;
    be_vector_delete(&vm->gbldesc.gvalist);
}

int be_globalvar_find(bvm *vm, bstring *name)
{
    bvalue *res = be_map_findstr(vm->gbldesc.idxtab, name);
    if (res) {
        return res->v.i;
    }
    return -1; /* not found */
}

int be_globalvar_new(bvm *vm, bstring *name)
{
    bglobaldesc *gd = &vm->gbldesc;
    int idx = be_globalvar_find(vm, name);
    if (idx == -1) {
        bvalue *desc;
        idx = be_map_count(gd->idxtab);
        desc = be_map_insertstr(gd->idxtab, name, NULL);
        var_setint(desc, idx);
        be_vector_resize(&gd->gvalist, idx + 1);
        vm->global = be_vector_data(&gd->gvalist);
        var_setnil(vm->global + gd->nglobal); /* set the new variable to nil */
        gd->nglobal++;
    }
    return idx;
}

void be_globalvar_release_space(bvm *vm)
{
    bglobaldesc *gd = &vm->gbldesc;
    be_map_release(vm, gd->idxtab);
    be_vector_release(&gd->gvalist);
    vm->global = be_vector_data(&gd->gvalist);
}
