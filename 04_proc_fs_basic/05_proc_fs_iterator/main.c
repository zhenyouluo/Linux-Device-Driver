#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include "main.h"
#include "fops.h"

static struct file_operations proc_fops = {
	.owner = THIS_MODULE,
	.open = proc_open,

	/* 
	 * seq_read, seq_lseek, seq_release are system function which help
	 * to implement the seq iterator
	 */
	.read = seq_read,
	.llseek = seq_lseek,
	.release = seq_release,
};

static
int __init m_init(void)
{
	printk(KERN_WARNING MODULE_NAME " is loaded\n");

	if (!proc_create(PROC_FILE_NAME, 0666, NULL, &proc_fops))
		return -ENOMEM;

	return 0;
}

static
void __exit m_exit(void)
{
	printk(KERN_WARNING MODULE_NAME " unloaded\n");
	remove_proc_entry(PROC_FILE_NAME, NULL);
}

module_init(m_init);
module_exit(m_exit);

MODULE_AUTHOR("d0u9");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("");
