# LinuxDrivers
This repository is a collection of Linux drivers examples.
Most of the information reported in this page are extracted from the book [Linux Device Driver Development - 2nd Edition](https://www.amazon.it/Linux-Device-Driver-Development-development-ebook/dp/B09TPDL3YH) (kernel v5.10)

## Chapter 2 - Building a Linux kernel module
See [skeleton module](./chapter2/0-skeleton/) to see the template of a module and how it can be build and loaded/removed.

### Building a kernel module
Two possible solutions can be used to build a kernel module:

* __Out-of-tree building__ Source code of the kernel is outside kernel directory. The module cannot be statically linked into the kernel, it must be loaded.
* __In-tree building__ Source code into the kernel directory. The module source code is used during the building process of the kernel.

#### Understanding the Linux kernel build system
The Linux kernel has its own build system (__kbuild__). It mainly realies on three files:

* ```KConfig```: Feature selections (mainly used with in-kernel tree building). 
* ```Kbuild or Makefile```: Compilation rules.
    If both exists, ```Kbuild``` will be used.

The command pattern to build a module with this tool is the following:
```
make -C $(KERNEL_SRC) M=$(shell pwd) [target]
# -C $(KERNEL_SRC): it indicates to make where is located prebuilt kernel directory
# M=$(shell pwd): it indicated where the Kbuild files is located (absolute path).
# [target] can have the following values:
    - modules (default)
    - modules_install
    - clean
```

To specify the type of module and the source files the following pattern is used: 
```
obj-<X> := <module_name>.o
# It builds <module_name>.o from <module_name>.c
# The result is <module_name>.ko
# <X> can have the following values:
#   -> m (loadable kernel module)
#   -> y (static-in kernel module)
#   -> "empty" (no build of the module)
```

If a module is composed by __multiple source files__ you can specify the following pattern:
```
<module_name>-y := <file1>.o <file2>.o
```
For example:
```
obj-m  := 8123.o
8123-y := 8123_if.o 8123_pci.o 8123_bin.o
# 8123 is built as a lodable module (obj-m)
# 8123 is built by building and linking 8123_if.o 8123_pci.o 8123_bin.o together
```
Example of [Makefile](./chapter2/0-skeleton/Makefile) for a skeleton Linux driver.

#### Out-of-tree building
Install kernel headers:
```
sudo apt update
sudo apt install linux-headers-$(uname -r)
```
Build kernel module
```
cd /kernel/module/path
make
```
Load/remove kernel and check the correctness
```
cd /kernel/module/path
sudo insmod <kernel_driver_name>.ko
sudo rmmod <kernel_driver_name>
dmesg
```
If you need to __cross-compile__ the kernel module, the following environment variables can be used:
```
make ARCH=riscv64 CROSS_COMPILE=riscv64-uknown-elf-gcc
```
#### In-tree building

### Handling module parameters