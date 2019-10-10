#include "cola_device.h"
#include <string.h>
#include <stdbool.h>


struct cola_device *device_list = NULL;

/*
    查找任务是否存在
*/
static bool cola_device_is_exists( cola_device_t *dev )
{
    cola_device_t* cur = device_list;
    while( cur != NULL )
    {
        if( strcmp(cur->name,dev->name)==0)
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}


static int device_list_inster(cola_device_t *dev)
{
    cola_device_t *cur = device_list;
    if(NULL == device_list)
    {
        device_list = dev;
        dev->next   = NULL;
    }
    else
    {
        while(NULL != cur->next)
        {
            cur = cur->next;
        }
        cur->next = dev;
        dev->next = NULL;
    }
    return 1;
}

/*
    驱动注册
*/
int cola_device_register(cola_device_t *dev)
{
    if((NULL == dev) || (cola_device_is_exists(dev)))
    {
        return 0;
    }

    if((NULL == dev->name) ||  (NULL == dev->dops))
    {
        return 0;
    }
    return device_list_inster(dev);

}
/*
    驱动查找
*/
cola_device_t *cola_device_find(const char *name)
{
    cola_device_t* cur = device_list;
    while( cur != NULL )
    {
        if( strcmp(cur->name,name)==0)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}
/*
    驱动读
*/
int cola_device_read(cola_device_t *dev,  int pos, void *buffer, int size)
{
    if(dev)
    {
        if(dev->dops->read)
        {
            return dev->dops->read(dev, pos, buffer, size);
        }
    }
    return 0;
}
/*
    驱动写
*/
int cola_device_write(cola_device_t *dev, int pos, const void *buffer, int size)
{
    if(dev)
    {
        if(dev->dops->write)
        {
            return dev->dops->write(dev, pos, buffer, size);
        }
    }
    return 0;
}
/*
    驱动控制
*/
int cola_device_ctrl(cola_device_t *dev,  int cmd, void *arg)
{
    if(dev)
    {
        if(dev->dops->control)
        {
            return dev->dops->control(dev, cmd, arg);
        }
    }
    return 0;
}
