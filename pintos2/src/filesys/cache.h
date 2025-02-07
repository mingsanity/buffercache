#ifndef FILESYS_CACHE_H
#define FILESYS_CACHE_H

#include "off_t.h"
#include "devices/block.h"
#include "threads/synch.h"
#include "lib/kernel/list.h"


#define CACHE_SIZE 64


struct CachedBlock
  {
    block_sector_t sector_num;
    bool valid;
    bool dirty;
    char data[BLOCK_SECTOR_SIZE];
    struct list_elem cache_elem;
    struct lock cache_lock;
  };


extern struct CachedBlock cache[CACHE_SIZE];
extern struct list cache_LRU;
extern struct lock cache_list_lock;


void initialize_cache_system (void);
void cache_flush_dirty_blocks (struct block *fs_device);
void cache_read (struct block *fs_device, block_sector_t sector_idx, void *buffer, off_t offset, int chunk_size);
void cache_write (struct block *fs_device, block_sector_t sector_idx, void *buffer, off_t offset, int chunk_size);
void cache_flush_block (struct block *fs_device, struct CachedBlock *LRU_block);
int get_cache_index(block_sector_t sector);
struct CachedBlock *get_CachedBlock (struct block *fs_device, block_sector_t sector, bool retrieve);
void cache_invalidate (struct block *fs_device);

size_t cache_hit_count (void);
size_t cache_miss_count (void);
size_t cache_write_count (void);
size_t cache_read_count (void);

#endif /* filesys/cache.h */
