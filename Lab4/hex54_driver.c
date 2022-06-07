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
#define DESCRIPTION "HEX54 DRIVER"

#define HEX54_MAJOR 0
#define HEX54_NAME "HEX54"
#define HEX54_MODULE_VERSION "HEX54 v0.1"

static int HEX54_major = 0;
static volatile int *HEX54_ptr;

int HEX54_open(struct inode *minode, struct file *mfile){
    HEX54_ptr = ioremap_nocache (LW_BRIDGE_BASE, LW_BRIDGE_SPAN) + HEX5_HEX4_BASE;
    printk(KERN_INFO "[HEX54_open]\n");
    return 0;
}

int HEX54_release(struct inode *minode, struct file *mfile){
    printk(KERN_INFO "[HEX54_release]\n");
    return 0;
}

ssize_t HEX54_write_byte(struct file *inode, const int *gdata, size_t length, loff_t *off_what){
    unsigned int c;
    get_user(c, gdata);
    *HEX54_ptr = c;
    return length;
}

static struct file_operations HEX54_fops = {
    .owner  = THIS_MODULE,
    .write  = HEX54_write_byte,
    .open   = HEX54_open,
    .release= HEX54_release,
};

int HEX54_init(void){
    int result = register_chrdev(HEX54_MAJOR, HEX54_NAME, &HEX54_fops);
    if(result < 0){
        printk(KERN_WARNING "Can't get any major\n");
        return result;
    }
    HEX54_major = result;
    printk(KERN_INFO "[HEX54_init] major number : %d\n", result);
    return 0;
}

void HEX54_exit(void){
    printk(KERN_INFO "[HEX54_exit]\n");
    unregister_chrdev(HEX54_major, HEX54_NAME);
}

module_init(HEX54_init);
module_exit(HEX54_exit);

MODULE_LICENSE(LICENSE);
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);