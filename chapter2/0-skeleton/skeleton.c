#include <linux/module.h>
#include <linux/init.h>

/**
 * This method is invoked every time the module is loaded
 */
static int __init skeleton_init(void) {
    pr_info("Skeleton module initialization!\n");
    return 0;
}

/**
 * This method is invoked every time the module is removed
 */
static void __exit skeleton_exit(void) {
    pr_info("Skeleton module exit!\n");
}

module_init(skeleton_init);
module_exit(skeleton_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mirco Mannino");
MODULE_DESCRIPTION("Linux Kernel module skeleton");