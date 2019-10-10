#ifndef _COLA_OS_H_
#define _COLA_OS_H_


#include <stdint.h>
#include <stdbool.h>



//任务事件
enum EVENT_SIG
{
    SIG_ALARM = 1 << 0,
    SIG_DATA  = 1 << 1,
    SIG_NOTE  = 1 << 2,
    SIG_UART  = 1 << 3,
    SIG_RADIO = 1 << 4,
    SIG_GPRS  = 1 << 5,
    SIG_USR1  = 1 << 8,
    SIG_USR2  = 1 << 9,
    SYS_EVENT_MSG  = 1 << 15,
};


enum
{
    TIMER_ALWAYS     = 0x00,
    TIMER_ONE_SHOT   = 0x01,
};


typedef void (*cbFunc)(uint32_t event);

typedef struct task_s
{
    uint8_t     timerNum;    //定时编号
    uint32_t    period;      //定时周期
    bool        oneShot;     //true只执行一次
    bool        start;       //开始启动
    uint32_t    timerTick;   //定时计数
    bool        run;         //任务运行标志 
    bool        taskFlag;    //任务标志是主任务还是定时任务
    uint32_t    event;       //驱动事件  
    cbFunc      func;        //回调函数
    struct task_s *next;
}task_t;

/*
    主循环任务创建
*/
int cola_task_create(task_t *task,cbFunc func);
/*
    主循环任务删除
*/
int cola_task_delete(task_t *task);
/*
    任务遍历，放到while(1)循环中
*/
void cola_task_loop(void);
/*
    定时任务创建
*/
int cola_timer_create(task_t *timer,cbFunc func);
/*
    启动定时任务
    one_shot：TIMER_ALWAYS   循环定时
              TIMER_ONE_SHOT 只运行一次
    time_ms :定时时间
*/
int cola_timer_start(task_t *timer,bool one_shot,uint32_t time_ms);
/*
    停止定时任务
*/
int cola_timer_stop(task_t *timer);

/*
    定时任务遍历，放到1ms ticker中
*/
void cola_timer_ticker(void);
/*
    设置任务事件
*/
int  cola_set_event(task_t *task,uint32_t sig_id);
/*
    取消任务事件
*/
int  cola_clear_event(task_t *task,uint32_t sig_id);

#endif 
