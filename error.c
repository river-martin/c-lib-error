#include "error.h"

Error error = { 0 };

jmp_buf err_jmp_target_env;

int err_jmp_target_env_set = 0;