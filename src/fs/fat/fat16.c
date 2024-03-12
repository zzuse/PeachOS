#include "fat16.h"
#include "string/string.h"
#include "status.h"

struct filesystem fat16_fs =
    {.resolve = fat16_resolve,
     .open = fat16_open};

struct filesystem *fat16_init()
{
    strcpy(fat16_fs.name, "FAT16");
    return 0;
}

int fat16_resolve(struct disk *disk)
{
    return -EIO;
}

void *fat16_open(struct disk *disk, struct path_part *path, FILE_MODE mode)
{
    return 0;
}
