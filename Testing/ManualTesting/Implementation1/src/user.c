/*******************************************************************************
 *                                         user.c
 ******************************************************************************/
/*******************************************************************************
 * @file user.c
 * @brief this file serves for manual testing.Here user is allowed to test the 
          functions.
 
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/

#include"memoryManagement.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ERR_NO_NUM        -1
#define ERR_NO_MEM        -2
#define MAX_SIZE          5000
#define INITIAL_ZERO      0
/*******************************************************************************
 * USER DATA TYPE
 ******************************************************************************/

/**typedef enum status
{
TRUE,
FALSE
}status; **/

/*******************************************************************************
 * API DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * Brief - Here user can test the functions as many times as he required.Two 
           menus are provided.one is main menu and the other is sub menu.In main
           menu user can test memory allocation,memory_free,memory_realloc,memory 
           _information and free_everything functions.In the sub menu user can 
           test memory_alloc and memory_calloc functions. 
 * Return - TRUE - always returns status as true. 
 ******************************************************************************/

int main()
{	
    int menuChoice = INITIAL_ZERO , subMenuChoice = INITIAL_ZERO, size = INITIAL_ZERO , totalElements = INITIAL_ZERO;
    char choice = 'y';
    int **pointer , count = INITIAL_ZERO , index2 = INITIAL_ZERO ;
    int	index , number = INITIAL_ZERO, *arrayPointer[MAX_SIZE], numFree = INITIAL_ZERO, numRealloc, *previousAddress, num = INITIAL_ZERO;
    pointer = arrayPointer;
    do
    {
    __fpurge(stdin);
    system("clear");
    printf("\n\n\t\tMENU\n\t1. Use memory_alloc or Use memory_calloc\n\t2. Use memory_free\n\t3. Use memory_realloc");
    printf("\n\t4. memory_information\n\t5. free Everything\n\t6. Display List");
    printf("\n\nEnter your menuChoice :");
    scanf("%d" , &menuChoice);
    switch(menuChoice)
    {
	case 1:	
	    system("clear");
	    printf("\n\n\t\tSUB-MENU\n\t1. Use memory_alloc \n\t2. Use memory_calloc\n\nEnter your choice :");
	    scanf("%d" , &subMenuChoice);
            switch(subMenuChoice)
            {
                case 1:
            	    system("clear");
	            printf("How many memory_alloc calls you want :");
	    	    scanf("%d",&num);
	    	    for(index = number ; index < number + num ; index++)
            	    {
 			printf("Enter size %d:",index + 1);
	    	        scanf("%d",&size);
 	        	*(pointer + index) = memory_alloc(size);
	    	    }
            	    printf("\nAddress\n------------\n");
            	    for(index = number ; index < number + num ; index++)
            	    {
            		printf("%p\n",*(pointer + index));
            		 
	    	    }
                    number = number + num;
		break;
		case 2:
            	    system("clear");
	            printf("How many memory_calloc calls you want :");
	    	    scanf("%d",&num);
	    	    for(index = number ; index < number + num ; index++)
	    	    {
	        	printf("Enter size %d:",index +1);
	    	        scanf("%d",&size);
			printf("Enter Total Elements of size %d :",size);
	    	        scanf("%d",&totalElements);
 	    		*(pointer + index) = memory_calloc(totalElements , size);
            	    }
            	    printf("\nAddress\n--------------------\n");
	    	    for(index = number ; index < number + num ; index++)
	    	    {
            		printf("%p\n",*(pointer + index));
            	    }
                    number = number + num;
		break;
                default:
		    system("clear");
		    printf("\nWrong Choice !!!");
                break;
	    }	
	break;

  	case 2:
	    system("clear");
            printf("How many memory_free calls you want :");
            scanf("%d",&count);
            for(index2 = 0 ; index2 < count ; index2++)
            {
                do
                {
	            printf("Out of %d which allocated space you want to free :",number);
 		    scanf("%d",&numFree);
	        }while(numFree > number || numFree <=0);
	    	printf("Number\tAddress\n-----------------\n");
	    	printf("%d\t%p\n",numFree,*(pointer + numFree-1));
                if(NULL != *(pointer+numFree-1))
	    	    memory_free(*(pointer+numFree-1));
            	for ( index = numFree - 1 ; index < number - 1 ; index++ )
            	{
		    *(pointer + index) = *(pointer + index +1);
             	}
            	number--;
     	    }
	break;

	case 3:
	    system("clear");
            printf("How many memory_realloc calls you want :");
            scanf("%d",&count);
            for(index2 = 0 ; index2 < count ; index2++)
            {
	        do
            	{
	            printf("Out of %d which allocated space you want to reallocate :",number);
 		    scanf("%d",&numRealloc);
	    	}while(numRealloc > number || numRealloc <=0);
            	printf("Enter new size :");
	    	scanf("%d",&size);
	    	previousAddress = *(pointer + numRealloc-1);
	    	printf("Previous_Address\tNew_SIZE\tNew_Adress\n----------------------------------------------------\n");
 	    	*(pointer + numRealloc-1) = memory_realloc(*(pointer + numRealloc-1),size);
            	printf("%p\t\t%d\t\t%p\n",previousAddress,size,*(pointer + numRealloc-1));
	    }	
	break;
	case 4:
            system("clear");
	    memory_information();
	break;
	case 5:
            system("clear");
	    for(index = 0 ; index < number ; index++)
    	    {
                if(NULL != *(pointer + index))		
 		    memory_free(*(pointer + index));
    	    }
            number = 0;
	break; 
	case 6:
            system("clear");
	    display_list();
	break;  
        default:
            system("clear");
	    printf("\nWrong Choice !!!!!!");
 	break;
    }
    printf("\nPress y to continue :");
    scanf(" %c",&choice);
    }while(choice == 'y' || choice == 'Y');
    return TRUE;
}


