/*******************************************************************************                                      
 *                        memoryManagement.c
 ******************************************************************************/
/*******************************************************************************
 * @file   memoryManagement.c
 * @brief  This program has the library functions for allocating memory,
		   deallocating memory and displaying the size of free memory and 
		   allocated memory.
		  *memory_alloc function-This function provides memory dynamically to 
		   user.  
          *memory_free function-This function frees the space allocated for the
		   user in the created heap space under user's request.
		  *memory_calloc function-This function provides memory dynamically to 
           user in asked number of blocks of specified size and intialise them 
		   to zero.
		  *memory_realloc function-This function reallocates memory to the 
	       previously allocated memory pointer by asking the user ,the already 
	       allocated pointer and size to be allocated.
		  *memory_size function- This function calculates the size of pointer.
		  *memory_information-This function gives the information about how much
		   memory is allocated and how much memory is free in given allocated
		   space.  
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/

#include <stddef.h>
#include "memoryManagement.h"

/*******************************************************************************
 * EXTERNAL VARIABLE DEFINITIONS
 ******************************************************************************/

in = INITIAL_ZERO ;
areaIndex = INITIAL_ZERO ;
sizeOfNode = sizeof( struct _info_area ) ;
struct _info_area *head = NULL , *current = NULL ;

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - This function provides memory dynamically to user. 
 
 * Param[in]  - size - It takes size as arguement from user 
 * Return     - It returns NULL if it can't give user required memory or it 
 * returns base address of the memory which it allocates to user dynamically.
 ******************************************************************************/

void *memory_alloc( int size )
{
    void *ptr ;
    if(size <= INITIAL_ZERO) /*if users asks for size 0 or less it prints error*/
    {
	printf("\nIvalid Size\n");
	return 0;
    }
    ptr = check_for_chunk_space( size ) ;
    /*first it search required memory from chunk spaces*/
    if( ptr )
    {	
	return ptr;
        /*if it finds required memory from chunk spaces then it return base
         * address from chunk space*/
    }
    /*if no space is available in chunk space then it search from available
     * memory */
    else
    {
	if(MAX_SIZE >= in + size)
	{	
	    ptr = &heapArea[in];
	    add_node_to_list( create_node ( size ) ) ;
	    return ptr ;
	}
/*if no memory is available from chunk or available memory then it returns NULL*/
	else
	{
	    return NULL;
	}
    }
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - This function adds a newly created _info_area to linked list.
 
 * Param[in]  - newNode - this take structure pointer as input(or a pointer)
 * pointing to newly created _info_area.
 * Return     - Always returns TRUE as status
 ******************************************************************************/

status add_node_to_list( struct _info_area *newNode )
{
    __fpurge( stdin );
    /*If linked list is empty*/
    if( NULL == head )
    {
	head = newNode ;
	current = newNode ;
    }
    /*If linked list is non empty*/
    else
    {
	current->next = newNode ;
	current = newNode ;
    }
    return TRUE;
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - This function creates a node in the info area to have a track of data
 * through linked list format. 
 * Param[in]  - size - It takes size as arguement from user .
 * Return     - returns the pointer for the created node to the linked list.
 ******************************************************************************/

struct _info_area* create_node( int size )
{
    struct _info_area *newNode ;
    newNode = (struct _info_area *)&infoArea[areaIndex] ;
    newNode->start = in ;
    newNode->status = FILLED ;
    newNode->end = in + size - EXCESS ;
    newNode->next = NULL ;
    areaIndex = areaIndex + sizeOfNode + EXCESS ;
    in = in + size ;
    return newNode ;
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - Gives the information about the memory allocated in the heap space
 * and free memory in the heap space.
 * Return     -  Always returns TRUE as status.
 ******************************************************************************/

#if 1
status memory_information()
{
    int chunkNumber = 1;
    int sum;
    int sumOfChunks = INITIAL_ZERO;
    struct _info_area *newNode;
    newNode=head;
    sum = INITIAL_ZERO ;
    while(newNode != NULL)
    {	
	if( FILLED == newNode->status)
	{
	sum = sum + newNode->end - newNode->start + EXCESS;
	}
	else
	{
	   printf("chunk #%d :%d\n", chunkNumber , newNode->end - newNode->start + EXCESS);
	   sumOfChunks=sumOfChunks +newNode->end - newNode->start + EXCESS;
	   chunkNumber++;
	}
	newNode=newNode->next;
    }
    printf("Total Memory is : %d\n", MAX_SIZE);
    printf("Memory in use : %d\n",  sum);
    printf("Total Free Memory other then Chunk is : %d\n", MAX_SIZE - sum);
    printf("Total free chunk Memory is : %d\n",  sumOfChunks);
    printf("Total Free Memory :%d\n\n",MAX_SIZE - sum + sumOfChunks);
    return TRUE;
}
#endif

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - This function frees the space allocated for the user in the created 
 * heap space under user's request.
 * Param[in]  - void pointer ,the pointer holding the address to be freed .
 * Return     - Always returns TRUE as status.
 ******************************************************************************/

status memory_free(void *pointer)
{
    struct _info_area *newNode;
    newNode = head;
    while((struct _info_area *)&heapArea[newNode->start]!=(struct _info_area *)pointer)
    {
	newNode=newNode->next;
    }
    newNode->status = EMPTY;/* status is again changed back to zero such that the 
						 * space to be freed can be used as chunk space.*/			
    return TRUE;
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - When memory is freed lots of chunk spaces remain inbetween. So this
 * function search if these is some chunk space in between which can be used when
 * memory_alloc is called by user.
 
 * Param[in]  - size - Size to be allocated to user
 * Return     - It returns NULL if no chunk space of size is available else
 * returns the base address of chunk space which is available.
 ******************************************************************************/

void *check_for_chunk_space(int size)
{
    struct _info_area *newNode;
    int temp;
    newNode=head;
    /* While loop checks if size required by user is less then memory available
    * in chunk spaces. If size can be allocated then status of _info_area is set to 1
    * which means this memory is now allocated. And remaing chunk space other
    * other then what allocated still have status as 0.
    */
    while(newNode!=NULL)
    {
	if((newNode->status == EMPTY) && (newNode->end - newNode->start +EXCESS >= size))
	{
	    temp = newNode->end;
	    newNode->status = FILLED; /*changing status to 1 if required size is available*/
	    newNode->end = newNode->start + size - EXCESS;
	    struct _info_area *newest_node;
	    newest_node = (struct _info_area *)&infoArea[areaIndex]; 
            /*createing new _info_area for remaining chunk space*/
	    newest_node->start = newNode->end + EXCESS;
	    newest_node->status = EMPTY;
	    newest_node->end = temp;
	    newest_node->next=newNode->next;
	    areaIndex = areaIndex + sizeOfNode + EXCESS;
	    newNode->next = newest_node;
	    return (void *)&heapArea[newNode->start];
            /*returning base address from available memory*/
	}	
	newNode=newNode->next;		
    }
    return NULL;
    /*returning NULL if required size is not available*/
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - This function provides memory dynamically to user in asked number of
 * blocks of specified size and intialise them to zero.
 * Param[in]  - nelem-number of blocks,elsize-size requested by the user.
 * Return     - It returns NULL if it can't give user required memory or it 
 * returns base address of the memory which it allocates to user dynamically.
 ******************************************************************************/

void *memory_calloc(int nelem, int elsize) 
{
    int size = nelem * elsize; 
    if(nelem <= 0 || elsize <= 0)
    {
	return 0;
    }
    void *ptr = memory_alloc(size);/* the total size is calculated and allocated
									* in the created heap space */ 
    memset(ptr, 0, size);/* the size intialised to zero */
    return ptr;
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - This function reallocates memory to the previously allocated memory 
 * pointer by asking the user ,the already allocated pointer and size to be 
 * allocated.  
 * Param[in]  - pointer to be realocated and size to be allocated.
 * Return     - It returns NULL if it can't give user required memory or it 
 * returns base address of the memory which it allocates to user dynamically.
 ******************************************************************************/

void * memory_realloc(void * ptr, int size)
{
    void *new;
    if (!ptr) /* if new memory need to be allocated then memory_alloc function 
               *is called and its address is returned to user */
    {
        new = memory_alloc(size);
    } 
    else 
    {
        if (memory_size(ptr) < size) 
		{
            new = memory_alloc(size);
 /* using memcpy the contents are moved from memory area source to the  
    memory area destination */
            memcpy(new, ptr, memory_size(ptr));
            memory_free(ptr);
        } 
		else 
		{
            new = ptr;
    	}
    }
    return new;
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - This function calculates the size of pointer.
 * Param[in]  - pointer given by the user.
 * Return     - memory_available-size of the pointer is returned.
 ******************************************************************************/

int memory_size(void *pointer)
{
    int memory_available = INITIAL_ZERO;
    struct _info_area *newNode;
    newNode=head;
    while((struct _info_area *)&heapArea[newNode->start]!=(struct _info_area *)pointer)
    {
	if((struct _info_area *)&heapArea[newNode->start]==(struct _info_area *)pointer)
	{
	     memory_available = newNode->end - newNode->start + EXCESS ;
        }	
	newNode=newNode->next;
    }
    return memory_available;
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - displays information about total memory,used memory,total free memory
 * other than chunk,total free memory and total free chunk memory.
 * Return     -true - always return true as status.
 ******************************************************************************/

#if 1
status display_list()
{
    int chunk_number = 1;
    int sum;
    int sumOfChunks = INITIAL_ZERO;
    struct _info_area *newNode;
    newNode = head;
    sum = INITIAL_ZERO;
    while(newNode != NULL)
    {
    /* status empty implies  chunk space is available and chunk space is 
       calculated */
	if(newNode->status == EMPTY)
	{
	    if(newNode->end - newNode->start > INITIAL_ZERO)
	    {
	    printf("chunk #%d :%d\n", chunk_number , newNode->end - newNode->start + EXCESS);
		sumOfChunks=sumOfChunks +newNode->end - newNode->start + EXCESS;
		chunk_number++;
	    }
	}
    /* calculates used memory */			
	else
	{
	    sum = sum + newNode->end - newNode->start + EXCESS;
	}
	newNode=newNode->next;
        printf("Total Memory is : %d\n", MAX_SIZE);
        printf("Memory in use : %d\n", sum);
    	printf("Total Free Memory other then Chunk is : %d\n", MAX_SIZE - sum);
    	printf("Total chunk Memory is : %d\n",  sumOfChunks);
    	printf("Total Free Memory :%d\n\n",MAX_SIZE - sum + sumOfChunks);
    }
    return TRUE;			
}
#endif


