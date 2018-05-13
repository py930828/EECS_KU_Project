/**
 * Buddy Allocator
 *
 * For the list library usage, see http://www.mcs.anl.gov/~kazutomo/list/
 */

/**************************************************************************
 * Conditional Compilation Options
 **************************************************************************/
#define USE_DEBUG 0

/**************************************************************************
 * Included Files
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "buddy.h"
#include "list.h"

/**************************************************************************
 * Public Definitions
 **************************************************************************/
#define MIN_ORDER 12
#define MAX_ORDER 20

#define PAGE_SIZE (1<<MIN_ORDER)
/* page index to address */
#define PAGE_TO_ADDR(page_idx) (void *)((page_idx*PAGE_SIZE) + g_memory)

/* address to page index */
#define ADDR_TO_PAGE(addr) ((unsigned long)((void *)addr - (void *)g_memory) / PAGE_SIZE)

/* find buddy address */
#define BUDDY_ADDR(addr, o) (void *)((((unsigned long)addr - (unsigned long)g_memory) ^ (1<<o)) \
									 + (unsigned long)g_memory)

#if USE_DEBUG == 1
#  define PDEBUG(fmt, ...) \
	fprintf(stderr, "%s(), %s:%d: " fmt,			\
		__func__, __FILE__, __LINE__, ##__VA_ARGS__)
#  define IFDEBUG(x) x
#else
#  define PDEBUG(fmt, ...)
#  define IFDEBUG(x)
#endif

/**************************************************************************
 * Public Types
 **************************************************************************/
typedef struct {
	int used;
	int order;
	int index;
	struct list_head list;
	/* TODO: DECLARE NECESSARY MEMBER VARIABLES */
} page_t;

/**************************************************************************
 * Global Variables
 **************************************************************************/
/* free lists*/
struct list_head free_area[MAX_ORDER+1];

/* memory area */
char g_memory[1<<MAX_ORDER];

/* page structures */
page_t g_pages[(1<<MAX_ORDER)/PAGE_SIZE];

/**************************************************************************
 * Public Function Prototypes
 **************************************************************************/

/**************************************************************************
 * Local Functions
 **************************************************************************/

/**
 * Initialize the buddy system
 */
void buddy_init()
{
	int i;
	int n_pages = (1<<MAX_ORDER) / PAGE_SIZE;
	for (i = 0; i < n_pages; i++) {
		/* TODO: INITIALIZE PAGE STRUCTURES */
		page_t new_page;
		new_page.index = i;
		new_page.used  = 0;
		new_page.order = 0;
		g_pages[i] = new_page;
	}

	/* initialize freelist */
	for (i = MIN_ORDER; i <= MAX_ORDER; i++) {
		INIT_LIST_HEAD(&free_area[i]);
	}

	/* add the entire memory as a freeblock */
	list_add(&g_pages[0].list, &free_area[MAX_ORDER]);
	g_pages[0].order = MAX_ORDER; // index 0 now refer to the entire memory
}

/**
 * Allocate a memory block.
 *
 * On a memory request, the allocator returns the head of a free-list of the
 * matching size (i.e., smallest block that satisfies the request). If the
 * free-list of the matching block size is empty, then a larger block size will
 * be selected. The selected (large) block is then splitted into two smaller
 * blocks. Among the two blocks, left block will be used for allocation or be
 * further splitted while the right block will be added to the appropriate
 * free-list.
 *
 * @param size size in bytes
 * @return memory block address
 */

int getOrderNum( int size )
{
	if( (1<<MAX_ORDER) < size )
	{
		printf( "%d is too big for the memory!!!, the biggest memory is %d.", size, 1<<MAX_ORDER );
		perror("");
	}
	for( int i = 0; i < MAX_ORDER; i++ )
	{
		if( (1<<i) >= size )	{ return i; }
	}
	return 1;
}

void *split( int CurrentOrder, int desired_order, page_t *page )
{
	if( CurrentOrder == desired_order ) // no need to split, return
	{
		return PAGE_TO_ADDR( page->index  );
	}
	CurrentOrder--;
	page->order--;
	int BuddyIndex = ADDR_TO_PAGE( BUDDY_ADDR( PAGE_TO_ADDR( page->index ), CurrentOrder ) );  // Get the buddy page
	g_pages[BuddyIndex].order = CurrentOrder; // change the Buddy page index
	list_add_tail( &g_pages[BuddyIndex].list, &free_area[CurrentOrder] );  // add buddy to the list
	return split( CurrentOrder, desired_order, page );
}

void *buddy_alloc(int size)
{
	/* TODO: IMPLEMENT THIS FUNCTION */
	int order = getOrderNum(size);
	int desired_order = order;
	page_t *page;
	for( ; order <= MAX_ORDER; order++ ) //find the block that is free
	{
		if( !list_empty( &free_area[order] ) )
		{
			struct list_head *ptr = free_area[order].next; // ptr point to the next head_list for backing up
			list_del_init(ptr);
			page = list_entry( ptr, page_t, list );
			page->used = 1; // page is now in used.
			return split( order, desired_order, page ); // split the block if it's bigger than neccesary
		}
		else if( order == MAX_ORDER )
		{
			printf("\nno free block for this size\n");
			return NULL;
		}
	}
	return NULL;
}


/**
 * Free an allocated memory block.
 *
 * Whenever a block is freed, the allocator checks its buddy. If the buddy is
 * free as well, then the two buddies are combined to form a bigger block. This
 * process continues until one of the buddies is not free.
 *
 * @param addr memory block address to be freed
 */
void buddy_free(void *addr)
{
	int index = ADDR_TO_PAGE(addr); page_t *page = &g_pages[index]; // get the page from the memory address
	page->used = 0;
	if( page->order == MAX_ORDER )
	{
		list_add_tail( &g_pages[index].list, &free_area[page->order] );
		return;
	}
	int BuddyIndex = ADDR_TO_PAGE( BUDDY_ADDR( addr, page->order ) );
	if( !g_pages[BuddyIndex].used && page->order == g_pages[BuddyIndex].order ) // if the buddy is not in used and they are the same size, combine them
	{
		if( BuddyIndex < index ) // should always referrence to the lower index
		{
			page = &g_pages[BuddyIndex];
		}
		page->order++;
		list_del_init( &g_pages[BuddyIndex].list );
		return buddy_free( PAGE_TO_ADDR( page->index ) );
	}
	else
	{
		list_add_tail( &g_pages[index].list, &free_area[page->order] );
		return;
	}
}

/**
 * Print the buddy system status---order oriented
 *
 * print free pages in each order.
 */
void buddy_dump()
{
	int o;
	for (o = MIN_ORDER; o <= MAX_ORDER; o++) {
		struct list_head *pos;
		int cnt = 0;
		list_for_each(pos, &free_area[o]) {
			cnt++;
		}
		printf("%d:%dK ", cnt, (1<<o)/1024);
	}
	printf("\n");
}
