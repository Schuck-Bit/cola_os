#ifndef _COLA_INIT_H_
#define _COLA_INIT_H_


#define  __used  __attribute__((__used__))

typedef void (*initcall_t)(void);

#define __define_initcall(fn, id) \
    static const initcall_t __initcall_##fn##id __used \
    __attribute__((__section__("initcall" #id "init"))) = fn; 

#define pure_initcall(fn)       __define_initcall(fn, 0) //可用作系统时钟初始化  
#define fs_initcall(fn)         __define_initcall(fn, 1) //tick和调试接口初始化
#define device_initcall(fn)     __define_initcall(fn, 2) //驱动初始化
#define late_initcall(fn)       __define_initcall(fn, 3) //其他初始化
    

void do_init_call(void);
    
#endif 
