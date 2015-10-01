/*******************************************************************************                                      
 *                        memoryManagement.c
 ******************************************************************************/

/*******************************************************************************
 * @file   memoryManagement.c
 * @brief  This program has the library functions for allocating memory,
           deallocating memory and displaying the size of free memory and 
	   allocated memory.

	  *memory_alloc function - This function provides memory dynamically to 
	                           user.  

      *memory_free function - This function frees the space allocated for the
			                  user in the created heap space under user's 
                              request.

      *memory_calloc function - This function provides memory dynamically to 
                                user in asked number of blocks of specified 
                                size and intialise them to zero.

     *memory_realloc function - This function reallocates memory to the 
	                            previously allocated memory pointer by asking  
                                the user ,the already allocated pointer and  
                                size to be allocated.

 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/

#include <stddef.h>
#include "memoryManagement.h"

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - This function performs allocation of memory in the heap space and 
 * returns the address to the user.
 * Param[in]  - minimum - Starting slot of Particular size.
 * Param[in]  - maximum - Ending slot of particular size.
 * Param[in]  - start -   Starting block of particular size.
 * Param[in]  - size  -  Block size used.
 * Return     - ptr   - Pointer pointing to current address.
 ******************************************************************************/

int perform_alloc ( int minimum , int maximum , int start ,int size)
{
    int index1,index2,blockNumber,end,flag=0,slotNumber;
    char *ptr;
    end = maximum - minimum ;
    /*base address of particular size */
    ptr = &totalMemoryArea[ start ]; 
    for( index2 = 0 ; index2 <= end ; index2++ )
    {
	flag = 0;
	for( index1 = 0 ; index1 < 8 ; index1++ )
	{
	    slotNumber = minimum + index2;
	    /*searching for first free block.*/
 	    if((totalMemoryArea[slotNumber] & 1<<index1) == 0) 
	    {
		//blockNumber = (8*index2) + index1 + 1 ;
		blockNumber = (8*index2) + index1  ;
		/*changing status of bit for allocated block.*/
		totalMemoryArea[slotNumber] = totalMemoryArea[slotNumber] | 1<<index1 ;  
		flag = 1 ;
		break;
	    }
        }
    	if(1 == flag)
    	break;
    }     
    /*checking whether all slot of partricular size are filled or not.*/
    if(1 == flag) 
    {      
	/*returning address of allocated block.*/
        return ptr + (blockNumber*size); 
    }
    else
    {
	return NULL;
    }
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - check_for_space- This function will checks for particular size block and 
 * returns the address of one block of particular size
 * Param[in]  - size - Size requested by user
 * Return     - ptr - address of first free block of size nearer to given by user
 ******************************************************************************/

void *check_for_space(int size)
{
    void *ptr;
    status currentStatus  = FALSE;
    if(size <= SIZE8 && currentStatus  == FALSE)
    {   /* call perform alloc to get address of some block of particular size*/
	ptr=perform_alloc( START_LENGTH_SIZE8 , END_LENGTH_SIZE8 , INITIAL_LENGTH_SIZE8 , SIZE8 ); 
	currentStatus =TRUE;
        if(NULL == ptr)
	{
	    /*if block of particular size is not available it will request for higher size block*/
	    currentStatus =FALSE;
	}
    }
    if(size <= SIZE16 && currentStatus  == FALSE)
    {
        ptr=perform_alloc( START_LENGTH_SIZE16 , END_LENGTH_SIZE16 , INITIAL_LENGTH_SIZE16 , SIZE16 );
	currentStatus =TRUE;
        if(NULL == ptr)
	{
	    currentStatus =FALSE;
	}
    }
    if(size <= SIZE32 && currentStatus  == FALSE)
    {
	ptr=perform_alloc( START_LENGTH_SIZE32 , END_LENGTH_SIZE32 , INITIAL_LENGTH_SIZE32 , SIZE32 );
	currentStatus =TRUE;
        if(NULL == ptr)
	{
	    currentStatus =FALSE;
	}
    }
    if(size <= SIZE64 && currentStatus  == FALSE)
    {
	ptr=perform_alloc( START_LENGTH_SIZE64 , END_LENGTH_SIZE64 , INITIAL_LENGTH_SIZE64 , SIZE64 );
	currentStatus =TRUE;
        if(NULL == ptr)
	{
	    currentStatus =FALSE;
	}
    }
    if(size <= SIZE128 && currentStatus  == FALSE)
    {
	ptr=perform_alloc( START_LENGTH_SIZE128 , END_LENGTH_SIZE128 , INITIAL_LENGTH_SIZE128 , SIZE128 );
	currentStatus =TRUE;
	if(NULL == ptr)
	{
	    currentStatus =FALSE;
	}
    }
    if(size <= SIZE256 && currentStatus  == FALSE)
    {
	ptr=perform_alloc( START_LENGTH_SIZE256 , END_LENGTH_SIZE256 , INITIAL_LENGTH_SIZE256 , SIZE256 );
	currentStatus =TRUE;
	if(NULL == ptr)
	{
	    currentStatus =FALSE;
	}
    }
    if(size <= SIZE512 && currentStatus  == FALSE)
    {
	ptr=perform_alloc( START_LENGTH_SIZE512 , END_LENGTH_SIZE512 , INITIAL_LENGTH_SIZE512 , SIZE512 );
	currentStatus =TRUE;
	if(NULL == ptr)
	{
	    currentStatus =FALSE;
	}
    }
    if(size <= SIZE1024 && currentStatus  == FALSE)
    {
	ptr=perform_alloc( START_LENGTH_SIZE1024 , END_LENGTH_SIZE1024 , INITIAL_LENGTH_SIZE1024 , SIZE1024 );
	currentStatus  = TRUE;
	if(NULL == ptr)
	{
	    currentStatus =FALSE;
	}
    }
    if(size <= SIZE2048 && currentStatus  == FALSE)
    {
	ptr=perform_alloc( START_LENGTH_SIZE2048 , END_LENGTH_SIZE2048 , INITIAL_LENGTH_SIZE2048 , SIZE2048 );
	currentStatus  = TRUE;
	if(NULL == ptr)
	{
	    currentStatus =FALSE;
	}
    }
    /*If user requires size greater than 500 then seperate space is also available*/
    if(currentStatus  == FALSE)
    {
	 ptr=NULL;
	
    }
    return ptr;
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - This function provides memory dynamically to user. 
 *
 * Param[in]  - size - It takes size as arguement from user.
 * 
 * Return     - It returns NULL if it can't give user required memory or it 
 *              returns base address of the memory which it allocates to user 
                dynamically.
 ******************************************************************************/

void *memory_alloc(int size)
{
    void *ptr;
    if(size <= 0) /*if users ask for size 0 or less it prints error and returns*/
    {
	printf("Invalid Size\n");
	return 0;
    }
    ptr = check_for_space(size);
    return ptr;	
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - This function frees the space allocated for the user in the created 
 *         heap space under user's request.
 * Param[in]  - void pointer ,the pointer holding the address to be freed .
 * Return     - Always returns TRUE as status.
 ******************************************************************************/

status memory_free(void *pointer)
{
    status currentStatus = FALSE;
    if( (&totalMemoryArea[INITIAL_LENGTH_SIZE8] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE8] >= pointer) )
    {
	currentStatus = delete_pointer( START_LENGTH_SIZE8 , INITIAL_LENGTH_SIZE8 , SIZE8 , pointer );     
    }
    else if( (&totalMemoryArea[INITIAL_LENGTH_SIZE16] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE16] >= pointer) )
    {
	currentStatus  = delete_pointer( START_LENGTH_SIZE16 , INITIAL_LENGTH_SIZE16 , SIZE16 , pointer );     
    }
    else if( (&totalMemoryArea[INITIAL_LENGTH_SIZE32] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE32] >= pointer) )
    {
	currentStatus  = delete_pointer( START_LENGTH_SIZE32 , INITIAL_LENGTH_SIZE32 , SIZE32 , pointer );     
    }
    else if( (&totalMemoryArea[INITIAL_LENGTH_SIZE64] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE64] >= pointer) )
    {
	currentStatus  = delete_pointer( START_LENGTH_SIZE64 , INITIAL_LENGTH_SIZE64 , SIZE64 , pointer );     
    }
    else if( (&totalMemoryArea[INITIAL_LENGTH_SIZE128] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE128] >= pointer) )
    {
	currentStatus  = delete_pointer( START_LENGTH_SIZE128 , INITIAL_LENGTH_SIZE128 , SIZE128 , pointer );     
    }
    else if( (&totalMemoryArea[INITIAL_LENGTH_SIZE256] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE256] >= pointer) )
    {
	currentStatus  = delete_pointer( START_LENGTH_SIZE256 , INITIAL_LENGTH_SIZE256 , SIZE256 , pointer );     
    }
    else if( (&totalMemoryArea[INITIAL_LENGTH_SIZE512] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE512] >= pointer) )
    {
	currentStatus  = delete_pointer( START_LENGTH_SIZE512 , INITIAL_LENGTH_SIZE512 , SIZE512 , pointer );     
    }
    else if( (&totalMemoryArea[INITIAL_LENGTH_SIZE1024] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE1024] >= pointer) )
    {
	currentStatus  = delete_pointer( START_LENGTH_SIZE1024 , INITIAL_LENGTH_SIZE1024 , SIZE1024 , pointer );     
    }
    else if( (&totalMemoryArea[INITIAL_LENGTH_SIZE2048] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE2048] >= pointer) )
    {
	currentStatus  = delete_pointer( START_LENGTH_SIZE2048 , INITIAL_LENGTH_SIZE2048 , SIZE2048 , pointer );     
    }
    else
    {
        currentStatus  = FALSE;
    }
    return currentStatus ;
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - This function is used to low the bit so that slot is freed ,this process
 * happens when memory_free function is called.
 * Param[in]  - minimum - Starting slot of Particular size.
 * Param[in]  - start -   Starting block of particular size.
 * Param[in]  - ptr-      pointer to be freed.   
 * Param[in]  - size  -   Block size used.
 * Param[out] - status -  Always returns TRUE as status.
 ******************************************************************************/

status delete_pointer(int minimum , int start , int size , void *ptr)
{
    unsigned char *pointer;
    int bits=255;
    pointer = (char *)ptr;
    int result = 0 , block = 0 , slot = 0;
    result = pointer - &totalMemoryArea[start];
    result = result / size;
    block = result / 8;
    slot = result % 8;
    bits ^= (-0 ^ bits) & (1 << slot);
    totalMemoryArea[minimum+block] = totalMemoryArea[minimum+block] & bits; 
    return TRUE;
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - This function provides memory dynamically to user in asked number of
 *         blocks of specified size and intialise them to zero.
 *
 * Param[in]  - nelem = number of blocks,elsize = size requested by the user.
 *
 * Return     - It returns NULL if it can't give user required memory or it 
 *              returns base address of the memory which it allocates to user 
                dynamically.
 ******************************************************************************/

void *memory_calloc(int nelem, int elsize) 
{
    int size = nelem * elsize; 
    if(nelem <= 0 || elsize <= 0)
    {
	return 0;
    }
    void *ptr = memory_alloc(size);
    memset(ptr, 0, size);
    return ptr;
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - This function reallocates memory to the previously allocated memory 
 *         pointer by asking the user ,the already allocated pointer and size
 *         to be allocated.  
 * Param[in]  - pointer to be realocated and size to be allocated.
 * Return     - It returns NULL if it can't give user required memory or it 
 *              returns base address of the memory which it allocates to user 
 *              dynamically.
 ******************************************************************************/

void * memory_realloc(void * ptr, int size)
{
    void *new;
    if (!ptr) 
    {
        new = memory_alloc(size);
    } 
    else 
    {
        if (memory_size(ptr) < size) 
	{
            new = memory_alloc(size);
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
 * Brief - This function tells memory size of block used by particular pointer
 
 * Param[in]  - ptr - it is pointer whose size this function will return
 * Return     - currentsize - size used by pointer
 ******************************************************************************/

int memory_size(void *ptr)
{
    char *pointer = NULL;
    pointer = (char *)ptr;
    int currentSize = 0;
    if( (&totalMemoryArea[INITIAL_LENGTH_SIZE8] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE8] >= pointer) )
    {
	currentSize = SIZE8;    
    }
    if( (&totalMemoryArea[INITIAL_LENGTH_SIZE16] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE16] >= pointer) )
    {
	currentSize = SIZE16; 
    }
    if( (&totalMemoryArea[INITIAL_LENGTH_SIZE32] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE32] >= pointer) )
    {
	currentSize = SIZE32;   
    }
    if( (&totalMemoryArea[INITIAL_LENGTH_SIZE64] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE64] >= pointer) )
    {
	currentSize = SIZE64; 
    }
    if( (&totalMemoryArea[INITIAL_LENGTH_SIZE128] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE128] >= pointer) )
    {
	currentSize = SIZE128;     
    }
    if( (&totalMemoryArea[INITIAL_LENGTH_SIZE256] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE256] >= pointer) )
    {
	currentSize = SIZE256;  
    }
    if( (&totalMemoryArea[INITIAL_LENGTH_SIZE512] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE512] >= pointer) )
    {
	currentSize = SIZE512; 
    }
    if( (&totalMemoryArea[INITIAL_LENGTH_SIZE1024] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE1024] >= pointer) )
    {
	currentSize = SIZE1024; 
    }
    if( (&totalMemoryArea[INITIAL_LENGTH_SIZE2048] <= pointer) && (&totalMemoryArea[MAX_LENGTH_SIZE2048] >= pointer) )
    {
	currentSize = SIZE2048;  
    }
    else
    {
        currentSize=0;
    }
    return currentSize;
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - block_information-This function used to display the satus of all
 * type of blocks,How many blocks of which size  is used and how may blocks
 * are free and how much percentage of blocks of every type is free.                          
 *
 * Return- The status of function true or false.
 ******************************************************************************/

#if 1
status block_information(void)
{
    int  count = 8  , kount , totalUsed=0, totalFree=0;
    printf("\n Size\t\tUsed_Blocks\t\tFree_Blocks\tPercent_Of_Used_Blocks\n---------------------------------------------------------------------------- ");
    for(kount = 1; kount <= 9 ; kount++)
    {
	printf("\n %d\t\t%d\t\t\t%d\t\t%f", count , used_blocks ( count ), unused_blocks ( count ),(float)(used_blocks ( count )*100)/(used_blocks ( count )+unused_blocks ( count )));
	totalUsed+=used_blocks(count);
	totalFree+=unused_blocks(count);        
	count =  count * 2;
    }
    printf("\n----------------------------------------------------------------------------");
    printf("\n Total\t\t%d\t\t\t%d",totalUsed,totalFree);
    printf("\n----------------------------------------------------------------------------\n");
    return TRUE;
}
#endif

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - used_block- This function is used to find out the number of used blocks
 *                     giving the size of block. 
 * Param[in]  - size
 * Return     - the total number of used blocks.
 ******************************************************************************/

int used_blocks(int size)
{
    int blocks;
    if(size == 8)
    {
	blocks = calculate_blocks(START_LENGTH_SIZE8 , END_LENGTH_SIZE8);
    }
    if(size == 16)
    {
	blocks = calculate_blocks(START_LENGTH_SIZE16 , END_LENGTH_SIZE16);
    }
    if(size == 32)
    {
	blocks = calculate_blocks(START_LENGTH_SIZE32 , END_LENGTH_SIZE32);
    }
    if(size == 64)
    {
	blocks = calculate_blocks(START_LENGTH_SIZE64 , END_LENGTH_SIZE64);
    }
    if(size == 128)
    {
	blocks = calculate_blocks(START_LENGTH_SIZE128 , END_LENGTH_SIZE128);
    }
    if(size == 256)
    {
	blocks = calculate_blocks(START_LENGTH_SIZE256 , END_LENGTH_SIZE256);
    }
    if(size == 512)
    {
	blocks = calculate_blocks(START_LENGTH_SIZE512 , END_LENGTH_SIZE512);
    }
    if(size == 1024)
    {
	blocks = calculate_blocks(START_LENGTH_SIZE1024 , END_LENGTH_SIZE1024);
    }
    if(size == 2048)
    {
	blocks = calculate_blocks(START_LENGTH_SIZE2048 , END_LENGTH_SIZE2048);
    }
   return blocks;
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - calulate_block-This function counts the number of used blocks of given 
 *         size.
 * Param[in]  - maximum and minimum block number of respective size.
 * Return     - The total count of used blocks.
 ******************************************************************************/

int calculate_blocks(int minimum , int maximum)
{
    int index1, index2, result = 0, end, slotNumber;
    char *ptr;
    end = maximum - minimum ;
    for( index2 = 0 ; index2 <= end ; index2++ )
    {
	for( index1 = 0 ; index1 < 8 ; index1++ )
	{
	    slotNumber = minimum + index2;
 	    if((totalMemoryArea[slotNumber] & 1<<index1) != 0)
	    {
		result++;
	    }
        }
    }
    return result;
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - free_block_information-This function used to display the satus of all
 * type of blocks,How many blocks of which size  is free and how many blocks 
 * and how much percentage of blocks of every type is free.                          
 *
 * Return- The status of function true or false.
 ******************************************************************************/

#if 0
status free_block_information(void)
{
    int  k = 8 , unUsedBlocks = 0 , kount ;
    for(kount = 1; kount <= 9 ; kount++)
    {
	unUsedBlocks = unused_blocks ( k ) ;
	//printf("\nunUsed blocks of size %d : %d", k , unUsedBlocks);
        k =  k * 2;
    }
}
#endif

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - unused_block- This function is used to find out the number of unused 
 * blocks giving the size of block. 
 * Param[in]  - size
 * Return     - the total number of unused blocks.
 ******************************************************************************/

int unused_blocks(int size)
{
    int blocks;
    if(size == 8)
    {
	blocks = calculate_free_blocks(START_LENGTH_SIZE8 , END_LENGTH_SIZE8);
    }
    if(size == 16)
    {
	blocks = calculate_free_blocks(START_LENGTH_SIZE16 , END_LENGTH_SIZE16);
    }
    if(size == 32)
    {
	blocks = calculate_free_blocks(START_LENGTH_SIZE32 , END_LENGTH_SIZE32);
    }
    if(size == 64)
    {
	blocks = calculate_free_blocks(START_LENGTH_SIZE64 , END_LENGTH_SIZE64);
    }
    if(size == 128)
    {
	blocks = calculate_free_blocks(START_LENGTH_SIZE128 , END_LENGTH_SIZE128);
    }
    if(size == 256)
    {
	blocks = calculate_free_blocks(START_LENGTH_SIZE256 , END_LENGTH_SIZE256);
    }
    if(size == 512)
    {
	blocks = calculate_free_blocks(START_LENGTH_SIZE512 , END_LENGTH_SIZE512);
    }
    if(size == 1024)
    {
	blocks = calculate_free_blocks(START_LENGTH_SIZE1024 , END_LENGTH_SIZE1024);
    }
    if(size == 2048)
    {
	blocks = calculate_free_blocks(START_LENGTH_SIZE2048 , END_LENGTH_SIZE2048);
    }
   return blocks;
}

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - calulate_free_block-This function counts the number of usused blocks of 
 * given size.
 * Param[in]  - maximum and minimum block number of respective size.
 * Return     - The total count of unused blocks.
 ******************************************************************************/

int calculate_free_blocks(int minimum , int maximum)
{
    int index1, index2, result = 0, end, slotNumber;
    char *ptr;
    end = maximum - minimum ;
    for( index2 = 0 ; index2 <= end ; index2++ )
    {
	for( index1 = 0 ; index1 < 8 ; index1++ )
	{
	    slotNumber = minimum + index2;
 	    if((totalMemoryArea[slotNumber] & 1<<index1) == 0)
	    {
		result++;
	    }
        }
    }
    return result;
}

