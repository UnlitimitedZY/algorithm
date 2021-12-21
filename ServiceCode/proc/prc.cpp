/*
 * @Author: your name
 * @Date: 2021-12-21 21:55:14
 * @LastEditTime: 2021-12-21 22:28:19
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /algorithm/ServiceCode/proc/prc.cpp
 */

//创建3个子进程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h> //信号相关头文件
#include <errno.h>  //errno
#include <unistd.h>

#include <iostream>

#define processNum 3;

static void worker_process_cycle()
{
    sigset_t set; //信号集

    sigemptyset(&set);                              //清空信号集
    if (sigprocmask(SIG_SETMASK, &set, NULL) == -1) //原来是屏蔽那10个信号【防止fork()期间收到信号导致混乱】，现在不再屏蔽任何信号【接收任何信号】
    {
        std::cout << "取消屏蔽信号集失败" << std::endl;
    }

    for (;;)
    {
        sleep(1);
        std::cout << "这是子进程" << getpid() << std::endl;
    }
}

static int spawn_process(int num)
{
    pid_t pid;

    pid = fork();

    switch (pid)
    {
    case -1:
        std::cout << "产生子进程失败" << std::endl;
        return -1;
    case 0:
        //为子进程，进入子进程从而做子进程的事情
        worker_process_cycle();
        break;
    default:
        break;
    }
    return 1;
}

static void start_work_processes(int num)
{
    while (num--)
    {
        //创建3个进程
        spawn_process(num);
    }
}

void prc_cyle()
{
    //首先屏蔽信号避免创建进程有干扰

    sigset_t set; //信号集

    //下列这些信号在执行本函数期间不希望收到【考虑到官方nginx中有这些信号，老师就都搬过来了】（保护不希望由信号中断的代码临界区）
    //建议fork()子进程时学习这种写法，防止信号的干扰；
    sigaddset(&set, SIGCHLD);  //子进程状态改变
    sigaddset(&set, SIGALRM);  //定时器超时
    sigaddset(&set, SIGIO);    //异步I/O
    sigaddset(&set, SIGINT);   //终端中断符
    sigaddset(&set, SIGHUP);   //连接断开
    sigaddset(&set, SIGUSR1);  //用户定义信号
    sigaddset(&set, SIGUSR2);  //用户定义信号
    sigaddset(&set, SIGWINCH); //终端窗口大小改变
    sigaddset(&set, SIGTERM);  //终止
    sigaddset(&set, SIGQUIT);  //终端退出符
    //.........可以根据开发的实际需要往其中添加其他要屏蔽的信号......

    //阻塞要屏蔽的信后1
    if (sigprocmask(SIG_BLOCK, &set, NULL) == -1)
    {
        std::cout << "sigprocmask error" << std::endl;
    }

    //创建子进程
    start_work_processes(3);

    //创建子进程后，父进程的执行流程会返回到这里，子进程不会走进来
    sigemptyset(&set); //信号屏蔽字为空，表示不屏蔽任何信号
    // 父进程在循环
    for (;;)
    {
        sleep(1); //休息一秒
        std::cout << "这是父进程"
                  << "pid" << getpid() << std::endl;
        sigsuspend(&set);
    }
}

int main()
{
    prc_cyle();
}