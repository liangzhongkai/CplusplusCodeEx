#include <setjmp.h>
#include <stdarg.h>
//#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#define READ_NON_BLOCKING_VERSION 1

// 版本1
#if ( READ_NON_BLOCKING_VERSION  == 1 )
extern volatile int invoke_count;
extern jmp_buf invoke_env;

void timeout_signal_handler(int sig);
typedef void (*sighandler_t)(int);
#define E_CALL_TIMEOUT (-9)

#define add_timeout_to_func(func, n, interval, ret, ...) \
{ \
    invoke_count = 0; \
    sighandler_t h = signal(SIGALRM, timeout_signal_handler); \
    if (h == SIG_ERR) { \
    ret = errno; \
    goto end; \
    }  \
    \
    if (sigjmp(invoke_env) != 0) { \
    if (invoke_count >= n) { \
    ret = E_CALL_TIMEOUT; \
    goto err; \
    } \
    } \
    \
    alarm(interval);\
    ret = func(__VA_ARGS__);\
    alarm(0); \
err:\
    signal(SIGALRM, h);\
end:\
    ;\
}
#endif

// 版本2
#if ( READ_NON_BLOCKING_VERSION  == 2 )
extern volatile int invoke_count;
extern sigjmp_buf invoke_env;

void timeout_signal_handler(int sig);
typedef void sigfunc(int sig);
sigfunc *my_signal(int signo, sigfunc* func);
#define E_CALL_TIMEOUT (-9)

#define add_timeout_to_func(func, n, interval, ret, …) \
{ \
    invoke_count = 0; \
    sigfunc *sf = my_signal(SIGALRM, timeout_signal_handler); \
    if (sf == SIG_ERR) { \
    ret = errno; \
    goto end; \
    }  \
    \
    if (sigsetjmp(invoke_env, SIGALRM) != 0) { \
    if (invoke_count >= n) { \
    ret = E_CALL_TIMEOUT; \
    goto err; \
    } \
    } \
    \
    alarm(interval); \
    ret = func(__VA_ARGS__);\
    alarm(0); \
err:\
    my_signal(SIGALRM, sf); \
end:\
    ;\
}
#endif


// 版本3
#if ( READ_NON_BLOCKING_VERSION  == 3 )

#endif
