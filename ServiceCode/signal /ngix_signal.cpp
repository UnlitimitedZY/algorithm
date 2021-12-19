/*
 * @Author: your name
 * @Date: 2021-12-19 21:15:14
 * @LastEditTime: 2021-12-19 23:10:35
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /algorithm/ServiceCode/signal /signal.cpp
 */

//采用sigaction 进行信号的处理

#include <signal.h> //信号相关头文件
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

#define ERROR -1
#define SUCCESS 0

typedef struct
{
    int signo;
    const char *signame;

    void (*handler)(int signo, siginfo_t *siginfo, void *ucontext); //信号处理函数指针
} nginx_signal_t;

void signal_handle(int signo, siginfo_t *siginfo, void *ucontext)
{
    std::cout << "received the signal :" << signo << std::endl;
}

//定义要处理的信号和信号处理函数
//函数指针绑定对应的信号处理函数
nginx_signal_t signalStus[] =
    {
        // signo      signame             handler
        {SIGHUP, "SIGHUP", signal_handle},   //终端断开信号，对于守护进程常用于reload重载配置文件通知--标识1
        {SIGINT, "SIGINT", signal_handle},   //标识2
        {SIGTERM, "SIGTERM", signal_handle}, //标识15
        {SIGCHLD, "SIGCHLD", signal_handle}, //子进程退出时，父进程会收到这个信号--标识17
        {SIGQUIT, "SIGQUIT", signal_handle}, //标识3
        {SIGIO, "SIGIO", signal_handle},     //指示一个异步I/O事件【通用异步I/O信号】
        {SIGSYS, "SIGSYS, SIG_IGN", NULL},   //我们想忽略这个信号，SIGSYS表示收到了一个无效系统调用，如果我们不忽略，进程会被操作系统杀死，--标识31
                                             //所以我们把handler设置为NULL，代表 我要求忽略这个信号，请求操作系统不要执行缺省的该信号处理动作（杀掉我）
        //...日后根据需要再继续增加
        {0, NULL, NULL} //信号对应的数字至少是1，所以可以用0作为一个特殊标记

};

int signal_init()
{
    nginx_signal_t *pSignalStu;
    struct sigaction sa;

    for (pSignalStu = signalStus; pSignalStu->signo != 0; pSignalStu++) //traversal :配置信号处理函数
    {
        memset(&sa, 0, sizeof(struct sigaction)); //初始化

        if (pSignalStu->handler)
        {
            //sa_sigaction：指定信号处理程序(函数)，注意sa_sigaction也是函数指针，是这个系统定义的结构sigaction中的一个成员（函数指针成员）；
            sa.sa_sigaction = pSignalStu->handler; //绑定信号处理函数

            //sa_flags：int型，指定信号的一些选项，设置了该标记(SA_SIGINFO)，就表示信号附带的参数可以被传递到信号处理函数中
            //SA_SIGINFO 代表这个信号处理函数生效
            sa.sa_flags = SA_SIGINFO;
        }
        else
        {
            //sa_handler:这个标记SIG_IGN给到sa_handler成员，表示忽略信号的处理程序，否则操作系统的缺省信号处理程序很可能把这个进程杀掉；
            //其实sa_handler和sa_sigaction都是一个函数指针用来表示信号处理程序。只不过这两个函数指针他们参数不一样， sa_sigaction带的参数多，信息量大，
            //而sa_handler带的参数少，信息量少；如果你想用sa_sigaction，那么你就需要把sa_flags设置为SA_SIGINFO
            sa.sa_handler = SIG_IGN; //对于信号处理函数为Null的代表忽视这个信号不让他采取默认的杀死动作
        }

        sigemptyset(&sa.sa_mask); //比如咱们处理某个信号比如SIGUSR1信号时不希望收到SIGUSR2信号，那咱们就可以用诸如sigaddset(&sa.sa_mask,SIGUSR2);这样的语句针对信号为SIGUSR1时做处理，这个sigaddset三章五节讲过；
                                  //这里.sa_mask是个信号集（描述信号的集合），用于表示要阻塞的信号，sigemptyset()这个函数咱们在第三章第五节讲过：把信号集中的所有信号清0，本意就是不准备阻塞任何信号；

        //参数1：要操作的信号
        //参数2：主要就是那个信号处理函数以及执行信号处理函数时候要屏蔽的信号等等内容
        //参数3：返回以往的对信号的处理方式【跟sigprocmask()函数边的第三个参数是的】，跟参数2同一个类型，我们这里不需要这个东西，所以直接设置为NULL；
        if (sigaction(pSignalStu->signo, &sa, NULL) == -1)
        {
            std::cout << "信号处理函数绑定失败" << std::endl;
            return ERROR;
        }
        else
        {
            std::cout << "绑定信号: " << pSignalStu->signame << "成功" << std::endl;
        }
    }

    return SUCCESS;
}

int main()
{
    signal_init();

    for (;;)
    {
    }
}