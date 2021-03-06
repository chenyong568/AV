


//
// Created by Administrator on 2018-03-01.
//

#include "XThread.h"
#include "XLog.h"

#include <thread>
using namespace std;
void XSleep(int mis)
{
    //?什么鬼
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}

void XThread::SetPause(bool isP)
{
    isPause = isP;
    //等待100毫秒
    for(int i = 0; i < 10; i++)
    {
        if(isPausing == isP)
        {
            break;
        }
        XSleep(10);
    }

}
//启动线程
bool XThread::Start()
{
    isExit = false;
    isPause = false;
    thread th(&XThread::ThreadMain,this);
    //当前线程放弃对创建的线程的控制
    th.detach();
    return true;
}
void XThread::ThreadMain()
{
    isRuning = true;
    XLOGI("线程函数进入");
    Main();
    XLOGI("线程函数退出");
    isRuning = false;
}


//通过控制isExit安全停止线程（不一定成功）
void XThread::Stop()
{XLOGI("Stop 停止线程begin!");
    isExit = true;
    for(int i = 0; i < 200; i++)
    {
        if(!isRuning)
        {
            XLOGI("Stop 停止线程成功!");

            return;
        }
        XSleep(1);
    }
    XLOGI("Stop 停止线程超时!");

}