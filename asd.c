/*
  mydrv.c - kernel 3.0 skeleton device driver
               copy_to_user()
 */
 
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
 
#include <linux/kernel.h>   /* printk() */
#include <linux/slab.h>   /* kmalloc() */
#include <linux/fs.h>       /* everything... */
#include <linux/errno.h>    /* error codes */
#include <linux/types.h>    /* size_t */
#include <asm/uaccess.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/device.h>
 
#define DEVICE_NAME "mydrv"
static int mydrv_major = 240;
module_param(mydrv_major, int, 0);
 
 
/*  구조체 포맷  */
typedef struct
{
   int age;  //나이 :35
   char name[30];// 이름 : HONG KILDONG
   char address[20]; // 주소 : SUWON CITY
   int  phone_number; // 전화번호 : 1234
   char depart[20]; // 부서 : ELAYER
} __attribute__ ((packed)) mydrv_data;
 
//   sprintf(k_buf->name,"HONG KILDONG");
 
static int mydrv_open(struct inode *inode, struct file *file)
{
  printk("mydrv opened !!\n");
  return 0;
}
 
static int mydrv_release(struct inode *inode, struct file *file)
{
  printk("mydrv released !!\n");
  return 0;
}
 
static ssize_t mydrv_read(struct file *filp, char __user *buf, size_t count,
                loff_t *f_pos)
{
  mydrv_data *k_buf;
  
  k_buf = (mydrv_data*)kmalloc(count,GFP_KERNEL);
 
  
  k_buf->age = 24;
  sprintf(k_buf->name,"%s","jhong");
  sprintf(k_buf->address,"%s","busan");
  k_buf->phone_number= 777;
  sprintf(k_buf->depart,"%s","system");
 
 
  
  if(copy_to_user(buf,k_buf,count))
      return -EFAULT;
  printk("mydrv_read is invoked\n");
  kfree(k_buf);
  return 0;
 
}
 
static ssize_t mydrv_write(struct file *filp,const char __user *buf, size_t count,
                            loff_t *f_pos)
{
  mydrv_data *k_buf;
    
  k_buf = (mydrv_data*)kmalloc(count,GFP_KERNEL);
 
  if(copy_from_user(k_buf,buf,count))
      return -EFAULT;
 
  printk("age = %d\n",k_buf->age);
  printk("name = %s\n",k_buf->name);
  printk("address = %s\n",k_buf->address);
  printk("phone = %d\n",k_buf->phone_number);
  printk("depart = %s\n",k_buf->depart);
 
  printk("mydrv_write is invoked\n");
  kfree(k_buf);
  return 0;
}
 
 
/* Set up the cdev structure for a device. */
static void mydrv_setup_cdev(struct cdev *dev, int minor,
        struct file_operations *fops)
{
    int err, devno = MKDEV(mydrv_major, minor);
    
    cdev_init(dev, fops);
    dev->owner = THIS_MODULE;
    dev->ops = fops;
    err = cdev_add (dev, devno, 1);
    
    if (err)
        printk (KERN_NOTICE "Error %d adding mydrv%d", err, minor);
}
 
 
static struct file_operations mydrv_fops = {
    .owner   = THIS_MODULE,
       .read       = mydrv_read,
        .write   = mydrv_write,
    .open    = mydrv_open,
    .release = mydrv_release,
};
 
#define MAX_MYDRV_DEV 1
 
static struct cdev MydrvDevs[MAX_MYDRV_DEV];
 
static int mydrv_init(void)
{
    int result;
    dev_t dev = MKDEV(mydrv_major, 0);
 
    /* Figure out our device number. */
    if (mydrv_major)
        result = register_chrdev_region(dev, 1, DEVICE_NAME);
    else {
        result = alloc_chrdev_region(&dev,0, 1, DEVICE_NAME);
        mydrv_major = MAJOR(dev);
    }
    if (result < 0) {
        printk(KERN_WARNING "mydrv: unable to get major %d\n", mydrv_major);
        return result;
    }
    if (mydrv_major == 0)
        mydrv_major = result;
 
    mydrv_setup_cdev(MydrvDevs,0, &mydrv_fops);
    printk("mydrv_init done\n");    
    return 0;
}
 
static void mydrv_exit(void)
{
    cdev_del(MydrvDevs);
    unregister_chrdev_region(MKDEV(mydrv_major, 0), 1);
    printk("mydrv_exit done\n");
}
 
module_init(mydrv_init);
module_exit(mydrv_exit);
 
MODULE_LICENSE("Dual BSD/GPL");
 


/* test_mydrv.c */
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
 
#define MAX_BUFFER 26
char buf_in[MAX_BUFFER], buf_out[MAX_BUFFER];
 
/*  구조체 포맷  */
typedef struct
{
   int age;  //나이 :35
   char name[30];// 이름 : HONG KILDONG
   char address[20]; // 주소 : SUWON CITY
   int  phone_number; // 전화번호 : 1234
   char depart[20]; // 부서 : ELAYER
} __attribute__ ((packed)) mydrv_data;
 
 
 
mydrv_data in;
mydrv_data out;
 
int main()
{
  int fd,i;
  
  fd = open("/dev/mydrv",O_RDWR);
  memset(&in, 0x00, sizeof(mydrv_data));
  memset(&out, 0x00, sizeof(mydrv_data));
 
  read(fd,&in,sizeof(mydrv_data));
 
  printf("age = %d\n",in.age);
  printf("name = %s\n", in.name);
  printf("address = %s\n",in.address);
  printf("phone = %d\n",in.phone_number);
  printf("depart = %s\n",in.depart); 
 
  out.age = 24;
  sprintf(out.name,"%s","jhong\x00");
  sprintf(out.address,"%s","busan\x00");
  out.phone_number = 777;
  sprintf(out.depart,"%s","system\x00");
 
  
 
  write(fd,&out,sizeof(mydrv_data));
  close(fd);
  return (0);
}
 


출처: https://richong.tistory.com/250?category=711909 [study]