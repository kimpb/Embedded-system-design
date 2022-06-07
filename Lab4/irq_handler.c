
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/uaccess.h>
#include <asm/io.h>
#include "address_map_arm.h"
#include "interrupt_ID.h"

#define LICENSE "KAU_EMBEDDED"
#define AUTHOR "IHCHAE"
#define DESCRIPTION "IRQ_HANDLER"

#define OFFSET 0xFFFFFF

void * LW_virtual;
void * DMA_virtual;
volatile int *DMA_ptr;
int * kmem;
int * vmem;
void * kmem_virt;
void * vmem_virt;
void * kmem_virtual;
volatile int * vmem_virtual;
volatile int *KEY_ptr;
volatile int *HEX30_ptr;
volatile int *HEX54_ptr;
volatile int *LEDR_ptr;
int count;

irq_handler_t irq_handler(int irq, void *dev_id, struct pt_regs *regs)
{
    count = count + 1;
    
    printk("kmem : %x, %x \n", kmem, *kmem);
    printk("kmem_virtual : %x \n", kmem_virtual);
    printk("vmem : %x, %x \n", vmem, *vmem);
    put_user(count, vmem);
    printk("vmem_virtual : %x\n", vmem_virtual);
    printk("DMA_ptr : %x, %x\n", DMA_ptr, *DMA_ptr);
    put_user(count, vmem_virtual);
    put_user(count, DMA_ptr);

    *(KEY_ptr + 3) = 0xF;



    return (irq_handler_t) IRQ_HANDLED;
}

static int __init initialize_pushbutton_handler(void)
{
    int value;
    LW_virtual = ioremap_nocache (LW_BRIDGE_BASE, LW_BRIDGE_SPAN);
    kmem = kmalloc(1, GFP_KERNEL);
    vmem = vmalloc(1);
    printk("kmem : %x, %x \n", kmem, *kmem);
    printk("vmem : %x, %x \n", vmem, *vmem);
    // kmem_virt = phys_to_virt(kmem);
    // kmem_virtual = (volatile int *) (kmem_virt);
    kmem_virtual = ioremap_nocache (kmem, 1);
    vmem_virtual = ioremap_nocache (vmem, 1);
    printk("kmem_virtual : %x", kmem_virtual);
    printk("vmem_virtual : %x", vmem_virtual);
    count = 0;
    *kmem = 0;
    // *kmem_virtual = 0;
    *vmem = 0;
    put_user(count, vmem);
    // copy_to_user(vmem_virtual, vmem_virtual, 1);
    // *vmem_virtual = 0;
    DMA_virtual = ioremap_nocache (SDRAM_BASE, SDRAM_SPAN);

    DMA_ptr = DMA_virtual + OFFSET;
    printk("DMA_virtual : %x\n", DMA_virtual);
    *DMA_ptr = 0;
    printk("DMA_ptr : %x, %x\n", DMA_ptr, *DMA_ptr);
    put_user(count, DMA_ptr);


    LEDR_ptr = LW_virtual + LEDR_BASE;
    *LEDR_ptr = 0;

    HEX30_ptr = LW_virtual + HEX3_HEX0_BASE;
    *HEX30_ptr = 0;
    HEX54_ptr = LW_virtual + HEX5_HEX4_BASE;
    *HEX54_ptr = 0;

    KEY_ptr = LW_virtual + KEY_BASE;
    *(KEY_ptr + 3) = 0x1;
    *(KEY_ptr + 2) = 0x1;

    value = request_irq (KEY_IRQ, (irq_handler_t) irq_handler, IRQF_SHARED, "pushbutton_irq_handler", (void *) (irq_handler));

    return value;

}

static void __exit cleanup_pushbutton_handler(void)
{
    *LEDR_ptr = 0;
    free_irq (KEY_IRQ, (void *) irq_handler);

}

module_init(initialize_pushbutton_handler);
module_exit(cleanup_pushbutton_handler);

MODULE_LICENSE(LICENSE);
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);
