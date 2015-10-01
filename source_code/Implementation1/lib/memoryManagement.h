/*******************************************************************************                                      
 *                        memoryManagement.h
 ******************************************************************************/
/*******************************************************************************
 * @file   memoryManagement.h
 * @brief  This program has the library functions for allocating memory,
		   deallocating memory and displaying the size of free memory and 
		   allocated memory.Here the memory management is done in stack segment
		   since the space called "Allocated heap Space" is assigned in stack
		   segment of the system architecture. 
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


#ifndef  MEMORYMANAGEMENT_H_
#define  MEMORYMANAGEMENT_H_

/*******************************************************************************
 * Include files
 ******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*******************************************************************************
 * MACRO DEFINITION
 ******************************************************************************/

#define MAX_SIZE       1024*1024
#define MAX_LENGTH     1024
#define INITIAL_ZERO   0
#define EXCESS         1
#define FILLED         1
#define EMPTY          0
/*******************************************************************************
 * ENUM DEFINATION
 ******************************************************************************/

typedef enum status
{
	TRUE,
	FALSE
}status;

/*******************************************************************************
 * STRUCTURE DEFINITION.THIS STRUCTURE DEFINES A NODE WHICH HAS THREE VARIABLES 
 * AND SELF REFERENCING POINTER WHICH POINTS TO ADDRES OF THE NEXT NODE.
*******************************************************************************/

struct _info_area
{
    int status;
    int start;
    int end;
    struct _info_area *next;
};

/*******************************************************************************
 * EXTERNAL VARIABLE DECLARATION
 ******************************************************************************/

static char heapArea[MAX_SIZE] ;
static char infoArea[MAX_LENGTH * sizeof( struct _info_area )] ;
extern int in , areaIndex , sizeOfNode ;

/*******************************************************************************
 * API DECLARATION
 ******************************************************************************/
struct _info_area* create_node(int size);
status add_node_to_list(struct _info_area *new_node);
status memory_free(void *pointer);
status memory_information();
status display_list();
void *memory_alloc( int size ); 
void *check_for_chunk_space(int size);
void *memory_realloc(void * ptr, int size);
void *memory_calloc(int nelem, int elsize);
int memory_size(void *ptr);
#endif /*  MEMORYMANAGEMENT_H_ */
