#ifndef _COLA_INIT_H_
#define _COLA_INIT_H_


#define  __used  __attribute__((__used__))

typedef void (*initcall_t)(void);

#define __define_initcall(fn, id) \
    static const initcall_t __initcall_##fn##id __used \
    __attribute__((__section__("initcall" #id "init"))) = fn; 

#define pure_initcall(fn)       __define_initcall(fn, 0) //������ϵͳʱ�ӳ�ʼ��  
#define fs_initcall(fn)         __define_initcall(fn, 1) //tick�͵��Խӿڳ�ʼ��
#define device_initcall(fn)     __define_initcall(fn, 2) //������ʼ��
#define late_initcall(fn)       __define_initcall(fn, 3) //������ʼ��
    

void do_init_call(void);
    
#endif 
