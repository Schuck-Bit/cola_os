#include "cola_os.h"
#include <stdio.h>
#include "bsp.h"
enum
{
    TASK_TASK   = 0x00,
    TASK_TIMER  = 0x01,
};

static struct task_s *task_list = NULL;
static volatile  uint8_t task_num = 0;

/*
    查找任务是否存在
*/
static bool cola_task_is_exists( task_t *task )
{
    task_t* cur = task_list;
    while( cur != NULL )
    {
        if( cur->timerNum == task->timerNum )
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

/*
    创建任务
*/
int cola_task_create(task_t *task,cbFunc func)
{
    task_t *cur  = task_list;
    OS_CPU_SR cpu_sr;
    enter_critical();
    if((NULL == task )||(cola_task_is_exists(task)))
    {
        exit_critical();
        return false;
    }
    task->taskFlag  = TASK_TASK;
    task->start     = true;
    task->run       = true; 
    task->func      = func;
    task->event     = 0;
    if(NULL == task_list)
    {
        task_num++;
        task->timerNum = task_num;
        task_list = task;
        task_list->next = NULL;
    }
    else
    {
        while((cur->next != NULL))
        {
            cur = cur->next;
        }
        task_num++;
        task->timerNum = task_num;
        cur->next = task;
        task->next = NULL;
    }
    exit_critical();
    return true;
}

/*
  删除指定任务
*/
int cola_task_delete(task_t *task)
{
    task_t *cur  = task_list;
    task_t *tmp  = NULL;
    OS_CPU_SR cpu_sr;
    enter_critical();
    while( cur != NULL )
    {
        if( cur->timerNum == task->timerNum )
        {
            tmp = cur->next;
            cur->next = tmp->next;
            exit_critical();
            return true;
        }
        cur = cur->next;
    }
    exit_critical();
    return false;
}
/*
  循环遍历任务链表
*/
void cola_task_loop(void)
{
    uint32_t events;
    task_t *cur  = task_list;
    OS_CPU_SR cpu_sr;
    
    while( cur != NULL )
    {
        if(cur->run)
        {
            if(NULL !=cur->func)
            {
                events = cur->event;
                if(events)
                {
                    enter_critical();
                    cur->event = 0;
                    exit_critical();
                }
                cur->func(events);                
            }
            if(TASK_TIMER == cur->taskFlag)
            {
                enter_critical();
                cur->run = false;
                exit_critical();
            }
            if((cur->oneShot)&&(TASK_TIMER == cur->taskFlag))
            {
               cur->start = false; 
            }
        }
        cur = cur->next;
    }
}

/*
  定时器创建
*/
int cola_timer_create(task_t *timer,cbFunc func)
{
    task_t *cur  = task_list;
    OS_CPU_SR cpu_sr;
    enter_critical();
    
    if((NULL == timer )||(cola_task_is_exists(timer)))
    {
        exit_critical();
        return false;
    }
    timer->taskFlag  = TASK_TIMER;
    timer->run       = false;
    timer->period    = 0;
    timer->oneShot   = true;
    timer->start     = false;
    timer->timerTick = 0;
    timer->func      = func;
    timer->event     = 0;
    if(NULL == task_list)
    {
        task_num++;
        timer->timerNum = task_num;
        task_list = timer;
        task_list->next = NULL;
    }
    else
    {
        while(cur->next != NULL)
        {
            cur = cur->next;
        }
        task_num++;
        timer->timerNum = task_num;
        cur->next = timer;
        timer->next = NULL;
    }
    exit_critical();
    return true;
    
}

/*
  定时器启动
*/
int cola_timer_start(task_t *timer,bool one_shot,uint32_t time_ms)
{
    task_t *cur  = task_list;
    OS_CPU_SR cpu_sr;
    enter_critical();
    while( cur != NULL )
    {
        if( cur->timerNum == timer->timerNum )
        {
            timer->period    = time_ms;
            timer->oneShot   = one_shot;
            timer->start     = true;
            timer->timerTick = 0;
            timer->taskFlag  = TASK_TIMER;
            exit_critical();
            return true;
        }
        cur = cur->next;
    }
    exit_critical();
    return false;
}
/*
  定时器停止
*/
int cola_timer_stop(task_t *timer)
{
    task_t *cur  = task_list;
    OS_CPU_SR cpu_sr;
    enter_critical();
    while( cur != NULL )
    {
        if( cur->timerNum == timer->timerNum )
        {
            timer->start     = false;
            exit_critical();
            return true;
        }
        cur = cur->next;
    }
    exit_critical();
    return false;
}
/*
  定时信息轮训
*/
void cola_timer_ticker(void)
{
    task_t *cur  = task_list;
    OS_CPU_SR cpu_sr;
    while( cur != NULL )
    {
        if((TASK_TIMER == cur->taskFlag)&& cur->start)
        {
            if(++cur->timerTick >= cur->period)
            {
                cur->timerTick = 0;
                if(cur->func != NULL)
                {
                    enter_critical();                   
                    cur->run = true;
                    exit_critical();
                }
            }
        }
        cur = cur->next;
    }
}

/*
  设置事件
*/
int cola_set_event(task_t *task,uint32_t sig_id)
{
    task_t *cur  = task_list;
    OS_CPU_SR cpu_sr;
    enter_critical();
    while( cur != NULL )
    {
        if( cur->timerNum == task->timerNum )
        {
            cur->event |= sig_id;
            exit_critical();
            return true;
        }
        cur = cur->next;
    }
    exit_critical();
    return false;
}
/*
  清除事件
*/
int  cola_clear_event(task_t *task,uint32_t sig_id)
{
    task_t *cur  = task_list;
    OS_CPU_SR cpu_sr;
    enter_critical();
    while( cur != NULL )
    {
        if( cur->timerNum == task->timerNum )
        {
            cur->event &= ~(sig_id);
            exit_critical();
            return true;
        }
        cur = cur->next;
    }
    exit_critical();
    return false;
}
