/**************************************************************************************************
* Filename:             osal_bsp.h
* Revised:        
* Revision:       
* Description:    
**************************************************************************************************/
#ifndef _CONFIG_H
#define _CONFIG_H

#ifdef __cplusplus

extern "C"
{
  
#endif

#include <stdio.h>    
 


    
#define USING_DEBUG
#ifdef USING_DEBUG
    #define os_log(...) printf(__VA_ARGS__)
   
#else
    #define os_log(...)
   
#endif

#ifndef USING_DEBUG
# define assert(p) ((void)0)
#else
# define assert(p) do { \
    if (!(p)) { \
        os_log("BUG at assert(%s)\n", #p); \
    }       \
 } while (0)
#endif
 
   
#ifdef __cplusplus
}
#endif

#endif 
