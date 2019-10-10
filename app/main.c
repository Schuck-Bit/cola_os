
#include "bsp.h"
#include "cola_os.h"
#include "app.h"
int main(void)
{
    disable_irq();
    bsp_init();
    app_init();
    enable_irq();
    while(1)
    {
        cola_task_loop();
    }
}

