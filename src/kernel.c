#include "kernel.h"
#include <stddef.h>
#include <stdint.h>
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "string/string.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "fs/file.h"
#include "disk/streamer.h"

uint16_t *video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char colour)
{
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void terminal_writechar(char c, char colour)
{
    if (c == '\n')
    {
        terminal_col = 0;
        terminal_row += 1;
        return;
    }
    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}

void terminal_initialize()
{
    video_mem = (uint16_t *)(0xB8000);
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }
}

void print(const char *str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 15);
    }
}

// extern void problem();
static struct paging_4gb_chunk *kernel_chunk = 0;
void kernel_main()
{
    terminal_initialize();
    print("Hello world init\ntest");

    // Initialize the heap
    kheap_init();

    // Initialize filesystem
    fs_init();

    // Search and initialize the disk;
    disk_search_and_init();

    // Initialize the interrupt descriptor table
    idt_init();

    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));

    // 6.
    // char *ptr = kzalloc(4096);
    // paging_set(paging_4gb_chunk_get_directory(kernel_chunk), (void *)0x1000, (uint32_t)ptr | PAGING_ACCESS_FROM_ALL | PAGING_IS_PRESENT | PAGING_IS_WRITEABLE);

    // Enable Paging
    enable_paging();

    // 7.
    // char buf[512];
    // disk_get(0);
    // disk_read_block(disk_get(0), 20, 4, &buf);

    // 5.
    // char buf[512];
    // disk_read_sector(0, 1, buf);

    // 4.
    // char *ptr2 = (char *)0x1000;
    // ptr2[0] = 'A';
    // ptr2[1] = 'B';
    // print(ptr2);
    // print(ptr);
    // Enable the system interrupts
    enable_interrupts();
    // 1. problem();

    // 2. outb(0x60, 0xff);

    // 3.
    // void *ptr = kmalloc(50);
    // void *ptr2 = kmalloc(5000);
    // void *ptr3 = kmalloc(5600);
    // kfree(ptr);
    // void *ptr4 = kmalloc(50);
    // if (ptr || ptr2 || ptr3 || ptr4)
    // {
    // }

    // 8.
    // struct path_root *root_path = pathparser_parse("0:/bin/shell.exe", NULL);
    // if (root_path)
    // {
    // }

    // 9.
    // struct disk_stream *stream = diskstreamer_new(0);
    // diskstreamer_seek(stream, 0x201);
    // unsigned char c = 0;
    // diskstreamer_read(stream, &c, 1);
    char buf[20];
    strcpy(buf, "hello!");
    while (1)
    {
    }
}