#ifndef ERROR_H
#define ERROR_H

#define MAX_ERR_MSG_LEN 1024
#include <setjmp.h>

extern int     err_jmp_target_env_set;
extern jmp_buf err_jmp_target_env;

typedef struct error {
    char msg[MAX_ERR_MSG_LEN];
    int  code;
} Error;

typedef enum error_code {
    BRU_NO_ERROR,
    BRU_ERR_NOT_IMPLEMENTED,
    BRU_ERR_UNREACHABLE // unexpectedly reached supposedly non-reachable code
} ErrorCode;

extern Error error;

/**
 * Set the error code and message.
 *
 * @param[in] code The error code.
 * @param[in] msg The error message.
 */
#define error_set(error_code, error_msg)                                  \
    do {                                                                  \
        error.code = error_code;                                          \
        int count  = snprintf(error.msg, MAX_ERR_MSG_LEN, "%s:%u:%s: %s", \
                              __FILE__, __LINE__, __func__, error_msg);   \
        if (count < 0) { printf("WARNING: error.msg truncated\n"); }      \
    } while (0)

#endif // ERROR_H
