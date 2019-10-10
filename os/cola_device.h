#ifndef _COLA_DEVICE_H_
#define _COLA_DEVICE_H_


#include "cola_init.h"

enum LED_state
{
    LED_OFF,
    LED_ON,
    LED_TOGGLE,

};

typedef struct cola_device  cola_device_t;

struct cola_device_ops
{
    int  (*init)   (cola_device_t *dev);
    int  (*open)   (cola_device_t *dev, int oflag);
    int  (*close)  (cola_device_t *dev);
    int  (*read)   (cola_device_t *dev, int pos, void *buffer, int size);
    int  (*write)  (cola_device_t *dev, int pos, const void *buffer, int size);
    int  (*control)(cola_device_t *dev, int cmd, void *args);

};

struct cola_device
{
    const char * name;
    struct cola_device_ops *dops;
    struct cola_device *next;
};

/*
    驱动注册
*/
int cola_device_register(cola_device_t *dev);
/*
    驱动查找
*/
cola_device_t *cola_device_find(const char *name);
/*
    驱动读
*/
int cola_device_read(cola_device_t *dev,  int pos, void *buffer, int size);
/*
    驱动写
*/
int cola_device_write(cola_device_t *dev, int pos, const void *buffer, int size);
/*
    驱动控制
*/
int cola_device_ctrl(cola_device_t *dev,  int cmd, void *arg);

#endif 
