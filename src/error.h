#ifndef ERROR_H
#define ERROR_H

#define MAX_ERR_MSG_LEN 1024
#include <setjmp.h>
#include <stdio.h>

typedef struct error
{
    char msg[MAX_ERR_MSG_LEN];
    int code;
} Error;

// Must be defined in the source file that includes this header
extern Error error;
extern int err_jmp_target_env_set;
extern jmp_buf err_jmp_target_env;

/**
 * Set the error code and message.
 *
 * @param[in] code The error code.
 * @param[in] msg The error message.
 */
#define error_set(error_code, error_msg)                                 \
    do                                                                   \
    {                                                                    \
        error.code = error_code;                                         \
        int count = snprintf(error.msg, MAX_ERR_MSG_LEN, "%s:%u:%s: %s", \
                             __FILE__, __LINE__, __func__, error_msg);   \
        if (count < 0)                                                   \
        {                                                                \
            printf("WARNING: error.msg truncated\n");                    \
        }                                                                \
    } while (0)

#endif // ERROR_H
