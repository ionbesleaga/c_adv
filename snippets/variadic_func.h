#ifndef VARIADIC_FUNC_H
#define VARIADIC_FUNC_H

typedef enum
{
    LOG_INFO,
    LOG_WARN,
    LOG_ERR
} log_level;

void log_msg(log_level level, const char *msg, ...);

#endif // VARIADIC_FUNC_H
