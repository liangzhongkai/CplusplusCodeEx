#include <stdafx.h>


////////////////////////////////////////////////////////
//
//    ���⣺���������෢����I/O���������̡����硢�����豸����������API���õȷ��档
//              �����ļ�/����I/O���������ǿ������ڷ������ļ���������select /poll�ĳ�ʱ�������������������ļ���������ϵͳ���ã�
//              ���ڵ�����API���棬����ʱ�����޷���select/poll�����г�ʱ��
//
//    ����1������select/poll���ó�ʱʱ��
//    ����2�����ö�ʱ��(alarm<�뼶>��setitimer<���뼶>)���ó�ʱʱ�䣬SIGALRM��������longjmp���������͵���֮ǰ���ﵽ��ʱ���������ͺ������õ�Ч��
//    ����3�����Ʒ���2���ǲ��������źţ�����������Ӧ���źŴ�����
//
//    �ο���http://tonybai.com/2013/10/25/add-timeout-to-blocking-function-call/
//
////////////////////////////////////////////////////////

//                      �汾1
#if ( READ_NON_BLOCKING_VERSION  == 1 )
volatile int invoke_count = 0;
jmp_buf invoke_env;

void
    timeout_signal_handler(int sig)
{
    invoke_count++;
    longjmp(invoke_env, 1);
}
#endif

//                      �汾2
#if ( READ_NON_BLOCKING_VERSION  == 2 )
volatile int invoke_count = 0;
sigjmp_buf invoke_env;

void
    timeout_signal_handler(int sig)
{
    invoke_count++;
    siglongjmp(invoke_env, 1);
}

sigfunc *
    my_signal(int signo, sigfunc *func)
{
    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    } else {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;
#endif
    }
    if (sigaction(signo, &act, &oact) < 0)
        return SIG_ERR;
    return oact.sa_handler;
}
#endif



//                       �汾3
#if ( READ_NON_BLOCKING_VERSION  == 3 )
#define add_timeout_to_func(func, n, interval, ret, ��) \
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
struct itimerval tick;  \
struct itimerval oldtick;  \
    tick.it_value.tv_sec = interval/1000; \
    tick.it_value.tv_usec = (interval%1000) * 1000; \
    tick.it_interval.tv_sec = interval/1000; \
    tick.it_interval.tv_usec = (interval%1000) * 1000; \
    \
    if (setitimer(ITIMER_REAL, &tick, &oldtick) < 0) { \
    ret = errno; \
    goto err; \
    } \
    \
    ret = func(__VA_ARGS__);\
    setitimer(ITIMER_REAL, &oldtick, NULL); \
err:\
    my_signal(SIGALRM, sf); \
end:\
    ;\
}
#endif

int main()
{
    #define MAXLINE 1024
    char line[MAXLINE];

    int ret = 0;
    int try_times = 3;
    int interval = 1000;
    //add_timeout_to_func(read, try_times, interval, ret, STDIN_FILENO, line, MAXLINE);
    add_timeout_to_func(read, try_times, interval, ret, 0, line, MAXLINE);
    if (ret == E_CALL_TIMEOUT) {
        printf("invoke read timeouts for 3 times\n");
        return -1;
    } else if (ret == 0) {
        printf("invoke read ok\n");
        return 0;
    } else {
        printf("add_timeout_to_func error = %d\n", ret);
    }
}