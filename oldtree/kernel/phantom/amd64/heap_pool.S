#include <kernel/config.h>
#include <kernel/page.h>

#include <amd64/asm.h>

    .bss
    .p2align PAGE_SHIFT

    .globl	EXT(phantom_start_heap_start)
EXT(phantom_start_heap_start):

    .space	PHANTOM_START_HEAP_SIZE

    .globl	EXT(phantom_start_heap_end)
EXT(phantom_start_heap_end):
	
    .data
    .globl	EXT(phantom_start_heap_size)
EXT(phantom_start_heap_size):
    .long	PHANTOM_START_HEAP_SIZE

