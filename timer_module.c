// timer_module.c
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kernel Toolkit Pro");
MODULE_DESCRIPTION("Simple Periodic Kernel Timer Module");
MODULE_VERSION("1.0");

/* ========= MODULE PARAMETER ========= */
static unsigned int interval = 1;   // seconds
module_param(interval, uint, 0644);
MODULE_PARM_DESC(interval, "Timer interval in seconds");

/* ========= TIMER STRUCT ========= */
static struct timer_list my_timer;

/* ========= TIMER CALLBACK ========= */
static void timer_callback(struct timer_list *t)
{
    pr_info("[timer_module] Timer triggered at %llu jiffies\n",
            (unsigned long long)jiffies);

    /* Restart the timer */
    mod_timer(&my_timer, jiffies + interval * HZ);
}

/* ========= INIT FUNCTION ========= */
static int __init timer_init(void)
{
    pr_info("Timer module loaded\n");

    timer_setup(&my_timer, timer_callback, 0);
    mod_timer(&my_timer, jiffies + interval * HZ);

    return 0;
}

/* ========= EXIT FUNCTION ========= */
static void __exit timer_exit(void)
{
    del_timer_sync(&my_timer);
    pr_info("Timer module unloaded\n");
}

module_init(timer_init);
module_exit(timer_exit);
