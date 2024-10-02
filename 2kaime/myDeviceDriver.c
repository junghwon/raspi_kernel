#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <asm/uaccess.h>

MODULE_LICENSE ("Dual BSD/GPL");

#define DRIVER_NAME "MyDevice"

/* このデバイスドライバで使うマイナー番号の開始番号と個数(＝デバイス数) */
static const unsigned int MINOR_BASE = 0;
static const unsigned int MINOR_NUM = 2;    /* マイナー番号は0〜1 */

/* このデバイスドライバのメジャー番号(動的に決める) */
static unsigned int mydevice_major;

/* キャラクタデバイスのオブジェクト */
static struct cdev mydevice_cdev;


/* open時に呼ばれる関数 */
static int myDevice_open (struct inode *inode, struct file *file)
{
    printk ("myDevice_open\n");
    return 0;
}

/* close時に呼ばれる関数 */
static int myDevice_close (struct inode *inode, struct file *file)
{
    printk ("myDevice_close\n");
    return 0;
}

/* read時に呼ばれる関数 */
static ssize_t myDevice_read (struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    printk ("myDevice_read\n");
    buf[0] = 'A';
    return 1;
}

/* write時に呼ばれる関数 */
static ssize_t myDevice_write (struct file *filp, const char __user *buf, size_t count, loff_t *fpos)
{
    printk ("myDeveice_write\n");
    return 1;
}

/* 各種システムコールに対応するハンドラテーブル */
struct file_operations s_myDevice_fops = {
    .open = myDevice_open,
    .release = myDevice_close,
    .read = myDevice_read,
    .write = myDevice_write,
};

/* ロード(insmod)時に呼ばれる関数 */
static int myDevice_init (void)
{
    printk ("myDevice_init\n");

    int alloc_ret = 0;
    int cdev_err = 0;
    dev_t dev;

    /* 1.空いているメジャー番号を確保する */
    alloc_ret = alloc_chrdev_region (&dev, MINOR_BASE, MINOR_NUM, DRIVER_NAME);
    if (alloc_ret != 0) {
        printk (KERN_ERR "alloc_chrdev_region = %d\n", alloc_ret);
        return (-1);
    }

    /* 2.取得したdev(＝メジャー番号　＋　マイナー番号)からメジャー番号を取得しておく */
    mydevice_major = MAJOR (dev);
    dev = MKDEV (mydevice_major, MINOR_BASE);

    /* 3.cdev構造体の初期化とシステムコールハンドラテーブルの登録 */
    cdev_init (&mydevice_cdev, &s_myDevice_fops);
    mydevice_cdev.owner = THIS_MODULE;

    /* 4.このデバイスドライバ(cdev)をカーネルに登録する */
    cdev_err = cdev_add (&mydevice_cdev, dev, MINOR_NUM);
    if (cdev_err != 0) {
        printk (KERN_ERR "cdev_add = %d\n", cdev_err);
        unregister_chrdev_region (dev, MINOR_NUM);
        return (-1);
    }    
 
    return 0;
}

/* アンロード(rmmod)時に呼ばれる関数 */
static void myDevice_exit (void)
{
    printk ("myDevice_exit\n");

    dev_t dev = MKDEV (mydevice_major, MINOR_BASE);

    /* 5.このデバイスドライバ(cdev)をカーネルから取り除く */
    cdev_del (&mydevice_cdev);

    /* 6.このデバイスドライバで使用していたメジャー番号の登録を取り除く */
    unregister_chrdev_region (dev, MINOR_NUM);
}

module_init (myDevice_init);
module_exit (myDevice_exit);
