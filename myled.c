/*************************************************************************

 
  Copyright (C) 2017  Ryota Tsuchiya
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
*************************************************************************/







#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include <linux/io.h>
#include <asm/uaccess.h> 
#include <linux/delay.h>
#include <linux/time.h>
#include <asm-generic/rtc.h>

MODULE_AUTHOR("Ryota Tsuchiya");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;
static volatile u32 *gpio_base1 = NULL;
static volatile u32 *gpio_base2 = NULL;
static volatile u32 *gpio_base3 = NULL;
static volatile u32 *gpio_base4 = NULL;
static volatile u32 *gpio_base5 = NULL;
static volatile u32 *gpio_base6 = NULL;
static volatile u32 *gpio_base7 = NULL;
static volatile u32 *gpio_base8 = NULL;
static volatile u32 *gpio_baseA = NULL;
static volatile u32 *gpio_baseB = NULL;
static volatile u32 *gpio_baseC = NULL;
static volatile u32 *gpio_baseD = NULL;

#define DELAY 0.1

int seg[18][7] =     {{7,7,7,7,7,7,10}, // 0
                     {10,7,7,10,10,10,10}, // 1
                     {7,7,10,7,7,10,7}, // 2
                     {7,7,7,7,10,10,7}, // 3
                     {10,7,7,10,10,7,7}, // 4
                     {7,10,7,7,10,7,7}, // 5
                     {7,10,7,7,7,7,7}, // 6
                     {7,7,7,10,10,10,10}, // 7
                     {7,7,7,7,7,7,7}, // 8
                     {7,7,7,7,10,7,7}, // 9
                     {7,7,7,10,7,7,7}, // A
                     {10,10,7,7,7,7,7}, // B(b)
                     {10,10,10,7,7,10,7}, // C(c)
                     {10,7,7,7,7,10,7}, // D(d)
                     {7,10,10,7,7,7,7}, // E
                     {7,10,10,10,7,7,7}, // F
                     {10,10,10,10,10,10,7}, // -
                     {10,10,10,10,10,10,10},// Blank
		     			
};
 struct rtc_time t;

#define LOG(msg, ...)				\
	_log(__FILE__, __LINE__);		\
	printk(msg, ## __VA_ARGS__)

static inline void _log(const char *file, const int line)
{
	get_rtc_time(&t);

	printk("%d %d:%d:%d %d: %s:%d: ",
	        t.tm_mday, t.tm_hour, t.tm_min,
               t.tm_sec, 2000 + (t.tm_year % 10), file, line);
}


static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
	char c;   //読み込んだ字を入れる変数
	if(copy_from_user(&c,buf,sizeof(char)))
	return -EFAULT;
	printk(KERN_INFO "receive %c\n",c);

	if(c=='0'){
       for(;;){
      gpio_base1[7] = 1 <<4 ;
	gpio_base2[7] = 1 <<17 ;
	gpio_base3[10] = 1 <<27 ;
	gpio_base4[7] = 1 << 22;
	gpio_base5[7] = 1 <<10 ;
	gpio_base6[10] = 1 <<9 ;
	gpio_base7[7] = 1 <<11 ;
	gpio_base8[10] = 1 <<7 ;
	gpio_baseA[10] = 1 <<14;
	gpio_baseB[7] = 1 <<15;
	gpio_baseC[7] = 1 <<18;
	gpio_baseD[7] = 1 <<23;
	msleep(DELAY);

	gpio_base1[7] = 1 <<4 ;
	gpio_base2[7] = 1 <<17 ;
	gpio_base3[7] = 1 <<27 ;
	gpio_base4[7] = 1 << 22;
	gpio_base5[7] = 1 <<10 ;
	gpio_base6[7] = 1 <<9 ;
	gpio_base7[10] = 1 <<11 ;
	gpio_base8[10] = 1 <<7 ;
	gpio_baseA[7] = 1 <<14;
	gpio_baseB[10] = 1 <<15;
	gpio_baseC[7] = 1 <<18;
	gpio_baseD[7] = 1 <<23;
	msleep(DELAY);

	gpio_base1[10] = 1 <<4 ;
	gpio_base2[7] = 1 <<17 ;
	gpio_base3[7] = 1 <<27 ;
	gpio_base4[10] = 1 << 22;
	gpio_base5[10] = 1 <<10 ;
	gpio_base6[10] = 1 <<9 ;
	gpio_base7[10] = 1 <<11 ;
	gpio_base8[10] = 1 <<7 ;
	gpio_baseA[7] = 1 <<14;
	gpio_baseB[7] = 1 <<15;
	gpio_baseC[10] = 1 <<18;
	gpio_baseD[7] = 1 <<23;
	msleep(DELAY);

	gpio_base1[7] = 1 <<4 ;
	gpio_base2[7] = 1 <<17 ;
	gpio_base3[7] = 1 <<27 ;
	gpio_base4[10] = 1 << 22;
	gpio_base5[10] = 1 <<10 ;
	gpio_base6[10] = 1 <<9 ;
	gpio_base7[10] = 1 <<11 ;
	gpio_base8[10] = 1 <<7 ;
	gpio_baseA[7] = 1 <<14;
	gpio_baseB[7] = 1 <<15;
	gpio_baseC[7] = 1 <<18;
	gpio_baseD[10] = 1 <<23;
	msleep(DELAY);
	}

}
	
	
	return 1;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write
};

static int __init init_mod(void)
{
	int retval;

	gpio_base = ioremap_nocache(0x3f200000, 0xA0);
	gpio_base1 = ioremap_nocache(0x3f200000, 0xA0);	
	gpio_base2 = ioremap_nocache(0x3f200000, 0xA0);
	gpio_base3 = ioremap_nocache(0x3f200000, 0xA0);	
	gpio_base4 = ioremap_nocache(0x3f200000, 0xA0);
	gpio_base5 = ioremap_nocache(0x3f200000, 0xA0);	
	gpio_base6 = ioremap_nocache(0x3f200000, 0xA0);
	gpio_base7 = ioremap_nocache(0x3f200000, 0xA0);
	gpio_base8 = ioremap_nocache(0x3f200000, 0xA0);
	gpio_baseA = ioremap_nocache(0x3f200000, 0xA0);
	gpio_baseB = ioremap_nocache(0x3f200000, 0xA0);
	gpio_baseC = ioremap_nocache(0x3f200000, 0xA0);
	gpio_baseD = ioremap_nocache(0x3f200000, 0xA0);

	const u32 led = 25;
	const u32 index = led/10;//GPFSEL2
	const u32 shift = (led%10)*3;//15bit
	const u32 mask = ~(0x7 << shift);//11111111111111000111111111111111
	gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);//001: output flag
	//11111111111111001111111111111111

	const u32 led1 = 4;
	const u32 index1 = led1/10;
	const u32 shift1 = (led1%10)*3;
	const u32 mask1 = ~(0x7 << shift1);
	gpio_base1[index1] = (gpio_base1[index1] & mask1) | (0x1 << shift1);
	
	const u32 led2 = 17;
	const u32 index2 = led2/10;
	const u32 shift2 = (led2%10)*3;
	const u32 mask2 = ~(0x7 << shift2);
	gpio_base2[index2] = (gpio_base2[index2] & mask2) | (0x1 << shift2);
	
	const u32 led3 = 27;
	const u32 index3 = led3/10;
	const u32 shift3 = (led3%10)*3;
	const u32 mask3 = ~(0x7 << shift3);
	gpio_base3[index3] = (gpio_base3[index3] & mask3) | (0x1 << shift3);
	
	const u32 led4 = 22;
	const u32 index4 = led4/10;
	const u32 shift4 = (led4%10)*3;
	const u32 mask4 = ~(0x7 << shift4);
	gpio_base4[index4] = (gpio_base4[index4] & mask4) | (0x1 << shift4);
	
	const u32 led5 = 10;
	const u32 index5 = led5/10;
	const u32 shift5 = (led5%10)*3;
	const u32 mask5 = ~(0x7 << shift5);
	gpio_base5[index5] = (gpio_base5[index5] & mask5) | (0x1 << shift5);

	const u32 led6 = 9;
	const u32 index6 = led6/10;
	const u32 shift6 = (led6%10)*3;
	const u32 mask6 = ~(0x7 << shift6);
	gpio_base6[index6] = (gpio_base6[index6] & mask6) | (0x1 << shift6);

	const u32 led7 = 11;
	const u32 index7 = led7/10;
	const u32 shift7 = (led7%10)*3;
	const u32 mask7 = ~(0x7 << shift7);
	gpio_base7[index7] = (gpio_base7[index7] & mask7) | (0x1 << shift7);

	const u32 led8 =7;
	const u32 index8 = led8/10;
	const u32 shift8 = (led8%10)*3;
	const u32 mask8 = ~(0x7 << shift8);
	gpio_base8[index8] = (gpio_base8[index8] & mask8) | (0x1 << shift8);

	const u32 ledA = 14;
	const u32 indexA = ledA/10;
	const u32 shiftA = (ledA%10)*3;
	const u32 maskA = ~(0x7 << shiftA);
	gpio_baseA[indexA] = (gpio_baseA[indexA] & maskA) | (0x1 << shiftA);

	const u32 ledB = 15;
	const u32 indexB = ledB/10;
	const u32 shiftB = (ledB%10)*3;
	const u32 maskB = ~(0x7 << shiftB);
	gpio_baseB[indexB] = (gpio_baseB[indexB] & maskB) | (0x1 << shiftB);

	const u32 ledC = 18;
	const u32 indexC = ledC/10;
	const u32 shiftC = (ledC%10)*3;
	const u32 maskC = ~(0x7 << shiftC);
	gpio_baseC[indexC] = (gpio_baseC[indexC] & maskC) | (0x1 << shiftC);

	const u32 ledD = 23;
	const u32 indexD = ledD/10;
	const u32 shiftD = (ledD%10)*3;
	const u32 maskD = ~(0x7 << shiftD);
	gpio_baseD[indexD] = (gpio_baseD[indexD] & maskD) | (0x1 << shiftD);

	retval = alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval<0){
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return retval;
	}
	printk(KERN_INFO "%s is loaded. major%d\n",__FILE__,MAJOR(dev));

	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
		printk(KERN_ERR "cdev_add faild. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
		return retval;
	}
	
	cls = class_create(THIS_MODULE,"myled");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
	}
	device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));
	return 0;
}

static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
        unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. major%d\n",__FILE__,MAJOR(dev));
	class_destroy(cls);	
}

module_init(init_mod);
module_exit(cleanup_mod);
