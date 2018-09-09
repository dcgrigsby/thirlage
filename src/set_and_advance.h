#define set_and_advance(variable_pointer, index_pointer) variable_pointer = index_pointer; index_pointer += sizeof(*variable_pointer)
