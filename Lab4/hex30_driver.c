#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/ioport.h>

#include <asm/uaccess.h>
#include <asm/io.h>

#include "address_map_arm.h"

#define LICENSE "KAU_EMBEDDED"
#define AUTHOR "IHCHAE"
#define DESCRIPTION "HEX30 DRIVER"

#define HEX30_MAJOR 0
#define HEX30_NAME "HEX30"
#define HEX30_MODULE_VERSION "HEX30 v0.1"
cd
static int HEX30_major = 0;
static volatile int *HEX30_ptr;

int HEX30_open(struct inode *minode, struct file *mfile){
    HEX30_ptr = ioremap_nocache (LW_BRIDGE_BASE, LW_BRIDGE_SPAN) + HEX3_HEX0_BASE;
    printk(KERN_INFO "[HEX30_open]\n");
    return 0;
}

int HEX30_release(struct inode *minode, struct file *mfile){
    printk(KERN_INFO "[HEX30_release]\n");
    return 0;
}

ssize_t HEX30_write_byte(struct file *inode, const int *gdata, size_t length, loff_t *off_what){
    unsigned int c;
    get_user(c, gdata);
    *HEX30_ptr = c;
    return length;
}

static struct file_operations HEX30_fops = {
    .owner  = THIS_MODULE,
    .write  = HEX30_write_byte,
    .open   = HEX30_open,
    .release= HEX30_release,
};

int HEX30_init(void){
    int result = register_chrdev(HEX30_MAJOR, HEX30_NAME, &HEX30_fops);
    if(result < 0){
        printk(KERN_WARNING "Can't get any major\n");
        return result;
    }
    HEX30_major = result;
    printk(KERN_INFO "[HEX30_init] major number : %d\n", result);
    return 0;
}

void HEX30_exit(void){
    printk(KERN_INFO "[HEX30_exit]\n");
    unregister_chrdev(HEX30_major, HEX30_NAME);
}

module_init(HEX30_init);
module_exit(HEX30_exit);

MODULE_LICENSE(LICENSE);
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);