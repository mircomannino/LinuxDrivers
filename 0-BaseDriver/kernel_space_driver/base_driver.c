#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>   /* printk() */
#include <linux/slab.h>     /* kmalloc() */
#include <linux/fs.h>       /* everything... */
#include <linux/errno.h>    /* error codes */
#include <linux/types.h>    /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>    /* O_ACCMODE */
#include <asm/uaccess.h>    /* copy_from/to_user */

#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,15)
#include <linux/config.h>
#endif

MODULE_LICENSE("Dual BSD/GPL");

/**
 * Description: TODO
 * 
 */

// Global Driver Memory
int DEVICE_MAJOR = 60;
const size_t SIZE = 32;
char* base_driver_buffer;

// Definition of function used to interact with the device file
int base_driver_open(struct inode* inode, struct file* filp);
int base_driver_release(struct inode* inode, struct file* filp);
ssize_t base_driver_read(struct file* filp, char* buf, size_t count, loff_t* f_pos);
ssize_t base_driver_write(struct file* filp, const char* buf, size_t count, loff_t* f_pos);
int base_driver_init(void);
void base_driver_exit(void);

// Struct to declare ususal file access functions
struct file_operations base_driver_fops =  {
    read:    base_driver_read,
    write:   base_driver_write, 
    open:    base_driver_open,
    release: base_driver_release
};


/**************************** Function implementations ********************************/
int base_driver_init(void) 
{
    // Device registering 
    int result = register_chrdev(DEVICE_MAJOR, "base_driver", &base_driver_fops);
    if(result < 0) 
    {
        printk("<1>base_driver: cannot obtain major number %d\n", DEVICE_MAJOR);
        return result;
    }
    // Allocate (kernel) memory for the buffer
    base_driver_buffer = kmalloc(SIZE, GFP_KERNEL);
    if(!base_driver_buffer) 
    {
        result = -ENOMEM;
        goto Fail;
    }
    memset(base_driver_buffer, 68, SIZE);
    printk("<1>base_driver: Adding the module\n");
    printk("<1>base_driver: set buffer to\n");
    printk("<1>START\n");
    size_t i = 0; 
    for(i = 0; i < SIZE; i++) printk("<1>%d\n", base_driver_buffer[i]);
    printk("<1>END\n");
    return 0; 

    Fail:
        base_driver_exit();
        return result;
}

void base_driver_exit(void)
{
    // Freeing the major number
    unregister_chrdev(DEVICE_MAJOR, "base_driver");
    // Freeing buffer memory
    if(base_driver_buffer)
        kfree(base_driver_buffer);
    printk("<1>base_driver: Removig the module\n");
}

int base_driver_open(struct inode* inode, struct file* filp)  
{
    printk("<1>base_driver: opening file\n"); 
    return 0; 
}

int base_driver_release(struct inode* inode, struct file* filp) 
{ 
    printk("<1>base_driver: closing file\n");
    return 0; 
}

ssize_t base_driver_read(struct file* filp, char* buf, size_t count, loff_t* f_pos) 
{
    // Transfering data to user space
    printk("<1>Read count: %zd\n", count); 
    const size_t current_size = (count < SIZE ? count : SIZE);
    if(copy_to_user(buf, base_driver_buffer, current_size))
    {
        printk("<1>base_driver: cannot copy to user sapce\n");
    }
    // Changing reading position as best suits
    if(*f_pos < SIZE) 
    {
        *f_pos += 1;
        return 1;
    }
    else 
    {
        return 0;
    }
}

ssize_t base_driver_write(struct file* filp, const char* buf, size_t count, loff_t* f_pos)
{
    // Transferring data from user space
    printk("<1>Write count: %zd\n", count); 
    const size_t current_size = (count < SIZE ? count : SIZE);
    const char* tmp = buf + current_size - 1;
    if(copy_from_user(base_driver_buffer, tmp, current_size))
    {
        printk("<1>base_driver: cannot copy from user space\n");
    }
    return 1;
}
/**************************************************************************************/

// Declaration of init and exit function
module_init(base_driver_init);
module_exit(base_driver_exit);

