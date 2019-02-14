#include "be_object.h"
#include "be_mem.h"

#ifdef BE_USE_IO_MODULE

#define READLINE_STEP       100

static int m_input(bvm *vm)
{
    size_t pos = 0, size = READLINE_STEP;
    char *buffer = be_malloc(size);
    char *res = be_fgets(stdin, buffer, (int)size);
    while (res) {
        pos += strlen(buffer + pos) - 1;
        if (!pos || buffer[pos] == '\n') {
            break;
        }
        size += READLINE_STEP;
        buffer = be_realloc(buffer, size);
        res = be_fgets(stdin, buffer + pos + 1, READLINE_STEP);
    }
    be_pushstring(vm, buffer);
    be_return(vm);
}

be_native_module_attr_table(attr_table) {
    be_native_module_function("input", m_input)
};

be_define_native_module(io, attr_table);

#endif /* BE_USE_IO_MODULE */
