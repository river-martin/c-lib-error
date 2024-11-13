#include <stdlib.h>

#include <error.h>

// Variables for error handling
jmp_buf err_jmp_target_env;
int err_jmp_target_env_set = 0;
Error error = {0};
typedef enum error_code
{
  ERR_CODE_NO_ERROR = 0,
  ERR_CODE_EXAMPLE,
} ErrorCode;

int main(void)
{
  if (setjmp(err_jmp_target_env) == 0)
  {
    err_jmp_target_env_set = 1;
    error_set(ERR_CODE_EXAMPLE, "This is an example error message");
    longjmp(err_jmp_target_env, 1);
  }
  else
  {
    printf("Error: %s\n", error.msg);
  }
  return EXIT_SUCCESS;
}
