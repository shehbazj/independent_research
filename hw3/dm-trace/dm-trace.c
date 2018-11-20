#include<linux/fs.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include <linux/bio.h>
#include <linux/slab.h>
#include <linux/blkdev.h>
#include <linux/device-mapper.h>
#include <linux/blk_types.h>

#define EXT4 1
#define BTRFS 2

/*
	A minimal trace device mapper tool that tracks bio requests sent by the application to the underlying device.
	
	Author: Shehbaz Jaffer
	Email: shehbaz@cs.toronto.edu
*/

struct my_dm_target {
        struct dm_dev *dev;
        sector_t start;
	bool error;
	int fsType;
	char mode;	// R | W | A
	unsigned long errorBlockNumber;
};

static int trace_map(struct dm_target *ti, struct bio *bio)
{
        struct my_dm_target *mdt = (struct my_dm_target *) ti->private;
	unsigned bsz;
	sector_t bno;

	bio_set_dev(bio, mdt->dev->bdev);
	bsz = bio->bi_iter.bi_size;
	
	if (bio_data_dir(bio) == WRITE) {
			printk(KERN_INFO "W %lu %u\n",bio->bi_iter.bi_sector / 8, bio->bi_iter.bi_size);
			bno = bio->bi_iter.bi_sector / 8;
	} else {
		if(bio->bi_iter.bi_size != 0) {
			printk(KERN_INFO "R %lu %u\n",bio->bi_iter.bi_sector / 8, bio->bi_iter.bi_size);
		}
	}

        submit_bio(bio);
        return DM_MAPIO_SUBMITTED;
}

static int 
trace_ctr(struct dm_target *ti,unsigned int argc,char **argv)
{
        struct my_dm_target *mdt;
        unsigned long long start;

        if (argc != 2) {
                ti->error = "Invalid argument count";
                return -EINVAL;
        }
        mdt = kmalloc(sizeof(struct my_dm_target), GFP_KERNEL);
        if(mdt==NULL)
        {
                ti->error = "dm-trace: Cannot allocate linear context";
                return -ENOMEM;
        }       
        if(sscanf(argv[1], "%llu", &start)!=1)
        {
                ti->error = "dm-trace: Invalid device sector";
                goto bad;
        }
        mdt->start=(sector_t)start;

//	r = setup_errorblock(mdt, ti);
        if (dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &mdt->dev)) {
                ti->error = "dm-trace: Device lookup failed";
                goto bad;
        }

	ti->num_flush_bios = 1;
	ti->num_discard_bios = 1;
	//ti->per_bio_data_size = sizeof(struct per_bio_data);
	ti->private = mdt;
        return 0;
  bad:
        kfree(mdt);
        return -EINVAL;
}

static void trace_dtr(struct dm_target *ti)
{
        struct my_dm_target *mdt = (struct my_dm_target *) ti->private;
        dm_put_device(ti, mdt->dev);
        kfree(mdt);
}


static int trace_end_io(struct dm_target *ti, struct bio *bio, blk_status_t *error)
{
	return DM_ENDIO_DONE;
}

static const struct block_device_operations dm_blk_dops;

static struct target_type trace = {
        .name = "trace",
        .version = {1,0,0},
        .module = THIS_MODULE,
        .ctr = trace_ctr,
        .dtr = trace_dtr,
        .map = trace_map,
	.end_io = trace_end_io,
};

static int init_trace(void)
{
        int result;
        result = dm_register_target(&trace);
        if(result < 0)
                printk(KERN_CRIT "\n Error in registering target \n");
        return 0;
}

static void cleanup_trace(void)
{
        dm_unregister_target(&trace);
}

MODULE_AUTHOR("Shehbaz Jaffer <shehbaz@cs.toronto.edu>");
module_init(init_trace);
module_exit(cleanup_trace);
MODULE_LICENSE("GPL");
