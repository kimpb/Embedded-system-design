
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

#include <linux/uaccess.h>
#include <asm/io.h>
#include "address_map_arm.h"
#include "interrupt_ID.h"

#define LICENSE "KAU_EMBEDDED"
#define AUTHOR "IHCHAE"
#define DESCRIPTION "IRQ_HANDLER"

#define OFFSET 0xFFFFFF

void * LW_virtual;
void * SDRAM_virtual;
volatile int *flag_ptr;
volatile int *KEY_ptr;
int flag;

irq_handler_t irq_handler(int irq, void *dev_id, struct pt_regs *regs)
{
    flag = 1;
    printk("interrupt!\n");
    
    put_user(flag, flag_ptr);

    *(KEY_ptr + 3) = 0xF;

    return (irq_handler_t) IRQ_HANDLED;
}

static int __init initialize_pushbutton_handler(void)
{
    int value;
    LW_virtual = ioremap_nocache (LW_BRIDGE_BASE, LW_BRIDGE_SPAN);
    
    flag = 0;

    SDRAM_virtual = ioremap_nocache (SDRAM_BASE, SDRAM_SPAN);

    flag_ptr = SDRAM_virtual + OFFSET;
    *flag_ptr = 0;
    put_user(flag, flag_ptr);

    KEY_ptr = LW_virtual + KEY_BASE;
    *(KEY_ptr + 3) = 0x1;
    *(KEY_ptr + 2) = 0x1;

    value = request_irq (KEY_IRQ, (irq_handler_t) irq_handler, IRQF_SHARED, "pushbutton_irq_handler", (void *) (irq_handler));

    return value;

}

static void __exit cleanup_pushbutton_handler(void)
{
    iounmap(SDRAM_virtual);
    free_irq (KEY_IRQ, (void *) irq_handler);

}

module_init(initialize_pushbutton_handler);
module_exit(cleanup_pushbutton_handler);

MODULE_LICENSE(LICENSE);
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);
