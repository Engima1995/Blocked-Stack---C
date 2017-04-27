#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "blocked_stack_int.h"

/*********************************************************************************************************************** 
*
* Author:
*
*	Sukhwinder Singh	-	28/11/2015
*
************************************************************************************************************************/

/*********************************************************************************************************************** 
*
* struct blocked_stack
* 
* Variables and Structures: 
* 
*	*items	--	this integer pointer is declared to hold the values until it reaches maximum size specified by the user
* 	*next	--	this is a structure that holds the previous values of the previous strucutre 
*
* Description: 
*
*	This is required for the stack_int_implmentation to keep record of the current/previously allocated blocks 
*	and their given values
*
* **********************************************************************************************************************/

struct blocked_stack{
	int *items;						// it will be used as an array implementation to hold values
	struct blocked_stack *next;		// it will be used to keep a reference to the next/previous node
};

/*********************************************************************************************************************** 
*
* struct stack_int_implementation
* 
* Variables and Structures: 
* 
*	*top		--	this is a structure that keeps hold of the current records and the previous records
* 	stack_size	--	this variable keeps count of the stack values, thereby incrementing/decrementing as values are pushed
*					or popped
*	block_size	--	this variable holds the value given by the user, to allocate a maximum size to a dynamically allocated
*					block
*	index 		--  this variable allows the program to correctly retrieve values or display values in a given allocated
*					stack
*
* Description: 
*
*	This is required to allocate new blocks and them as a reference once they reached their maximum capacity, so
*	new blocks can be allocated. This is can also be used vice versa, to deallocate blocks. It helps the program
*	to keep track of it's current state
*
* **********************************************************************************************************************/

struct stack_int_implementation{
	struct blocked_stack *top;		// it will be used to hold current records and previous records
	int stack_size;					// holds the value which indicates the number of items in the blocked stacks
	int block_size;					// refers to the maximum size a block can have
	int index;						// holds record of the current index within the blocked stack
};

/*********************************************************************************************************************** 
*
* stack_int * new_blocked_stack_int (int block_size)
*
* Parameters:
* 
*	block_size	--	this parameter refers to the input that the user gives, so the dynamically allocated stack 
*					is given a maximum size
*
* Variables and Structures: 
* 
*	*top		--	this is a structure that keeps hold of the current records and the previous records
* 	stack_size	--	this variable keeps count of the stack values, thereby incrementing/decrementing as values are pushed
*					or popped
*	block_size	--	this variable holds the value given by the user, to allocate a maximum size to a dynamically allocated
*					block
*	index 		--  this variable allows the program to correctly retrieve values or display values in a given allocated
*					stack
*
* Description: 
*
*	This is required to allocate new blocks and them as a reference once they reached their maximum capacity, so
*	new blocks can be allocated. This is can also be used vice versa, to deallocate blocks. It helps the program
*	to keep track of it's current state
*
* **********************************************************************************************************************/

stack_int * new_blocked_stack_int(int block_size){
	stack_int * s = (stack_int *)malloc(sizeof(stack_int*));	// allocates memory on heap for the structure s
	s->top = NULL;												// current top points to NULL
	s->block_size = block_size;									// blocks will have a max size of the input parameter value
	s->index = 0;												// current index points to 0
	s->stack_size = 0;											// curren size of the stack is 0
	return s;
}

/*********************************************************************************************************************** 
*
* int stack_int_isempty (stack_int *s)
*
* Parameters:
* 
*	*s 			--	this parameter refers to the stack the user will use as an input, it will be used to point to the
					given stack as a reference
*
* Description: 
*
*	This function is required to check the whether or not the given stack size is empty or not, it can also be used
*	in other functions to help manipulate certain pieces of data
*
* **********************************************************************************************************************/

int stack_int_isempty(stack_int *s){
	assert(s!=NULL);
	return s->stack_size == 0;		//returns true if the size of the referenced stack is 0, meaning empty else false
}

/*********************************************************************************************************************** 
*
* int stack_int_size (stack_int *s)
*
* Parameters:
* 
*	*s 			--	this parameter refers to the stack the user will use as an input, it will be used to point to the
					given stack as a reference
*
* Description: 
*
*	This function is required to find the current size of the given stack, it can also be used
*	in other functions to help manipulate certain pieces of data
*
* **********************************************************************************************************************/

int stack_int_size(stack_int *s){
	assert(s!=NULL);
	return s->stack_size;			// returns the current size of the stack
}

/*********************************************************************************************************************** 
*
* void stack_int_push (stack_int *s, int x)
*
* Parameters:
* 
*	*s 			--	this parameter refers to the stack the user will use as an input, it will be used to point to the
*					given stack as a reference
*
*	x			--	this refers to the value that the user will give as an input, which can then be pushed on to the 
*					stack
*
* Variables and Structures: 
* 
*	*b 			--	refers to the blocked_stack structure, which will be used as a temporary storage to store values
*					for the stack, which later the stack uses it to update it's fields
*
* Description: 
*
*	This function is a fundamental part of the stack, it allows values to be pushed into the referenced stack, it uses
*	temporary allocated blocked_stack *b, to hold values which it is later used by the stack itself to update its fields
*
* **********************************************************************************************************************/

void stack_int_push(stack_int *s, int x){

	assert(s!=NULL);

	struct blocked_stack *b;		/* b refers to a temporary blocked_stack strucutre which will hold values
									 * for the referenced stack to hold 
									 */
	if(s->index == s->block_size || s->stack_size == 0){	// this initialises a new block either when empty or full

		b = (struct blocked_stack *)malloc(sizeof(struct blocked_stack));

		if(b==NULL){										// if memory couldn't be allocated then exit from the program
			printf("Failed to allocate memory !\n");
			exit(1);
		}

		b->items = (int *)malloc(sizeof(int) * s->block_size);	// items now becomes an array with the provided block_size
		b->next = s->top;					  // b will hold a value of NULL when there are no blocks/else the current top
		s->top = b;							  /* s->top now holds the current value of b, which has a reference to NULL and
											   * the current array of items
											   */
		s->index = 0;						  // index is set to 0, so items can be populated correctly using index
		
	}

	s->top->items[s->index] = x;			  // items are now being added to the current index and to the current array
	(s->index)++;							  // index and stack_size are now increased as it holds a value
	(s->stack_size)++;
		
}

/*********************************************************************************************************************** 
*
* void stack_int_pop (stack_int *s)
*
* Parameters:
* 
*	*s 			--	this parameter refers to the stack the user will use as an input, it will be used to point to the
*					given stack as a reference
*
* Variables and Structures: 
* 
*	*b 			--	refers to the blocked_stack structure, which will be used as a temporary storage to store values
*					for the stack, which later the stack uses it to update it's fields
*
* Functions:
*
*	stack_int_isempty(s) 			-- this function is used to check whether the referenced stack is empty or not,
*									   if it is then the program will end becasue there is no value to be popped,
*									   otherwise the values are popped one by one	
*
* Description: 
*
*	This function is a fundamental part of the stack, it allows values to be popped out of the referenced stack, it uses
*	temporary allocated blocked_stack *b to hold values which it is later used by the stack itself to update its fields
*
* **********************************************************************************************************************/

void stack_int_pop(stack_int * s){
		
	struct blocked_stack * b;		/* b refers to a temporary blocked_stack strucutre which will hold values
									 * for the referenced stack to hold 
									 */

	if(stack_int_isempty(s)){		// If the stack is empty then there is nothing to be popped so the program exits
		printf("Stack is empty");
		exit(1);
	}else if(s->index == 1){		// If index is equal to 1, then we want to deallocate the block
		b=(struct blocked_stack *)malloc(sizeof(struct blocked_stack));		// Allocates enough memory so b could copy
		b->next = s->top;													// all the values stored in s, which can be
		b->items = s->top->items;											// deallocated and s could become the next
		s->top = s->top->next;												// block that was previously allocated
		free(b);
		s->index = s->block_size + 1;										// index now becomes maximum block size
	}																		// so it can be used to find items in current block

	(s->index)--;															// decrease index and size
	(s->stack_size)--;
}

/*********************************************************************************************************************** 
*
* int stack_int_top (stack_int *s)
*
* Parameters:
* 
*	*s 			--	this parameter refers to the stack the user will use as an input, it will be used to point to the
*					given stack as a reference
*
* Description: 
*
*	This function returns the top value of the referenced stack
*
* **********************************************************************************************************************/

int stack_int_top(stack_int *s){

	return s->top->items[s->index-1];		// Locates top value in the stack

}

/*********************************************************************************************************************** 
*
* void stack_int_display (stack_int *s)
*
* Parameters:
* 
*	*s 			--	this parameter refers to the stack the user will use as an input, it will be used to point to the
*					given stack as a reference
*
* Variables and Structures: 
* 
*	*tmp		--	refers to the stack_int structure, which will be used as a temporary storage to reference the exact
*					values of the referenced stack, it is used so that the referenced stack does not get overwritten
*					or loses any information. It is used as a safety pre-caution
*
*	*current	--	refers to the stack_int structure, which will be used as a tracker storage to reference the current
*					node within the structure. It is useful for the tmp structure during manipulation of the display function
*					to keep track of the top node value
*
*	num_blocks 	--	refers to the number of blocks that have been allocated. It is calucalted by using the values of the
*					allocated blocks divided by the maximum block_size of a block, which returns a value. If value is 0, 
*					then it basically means there is 1 block avaliable else it is checked using stack_int_size(tmp) 
*					greater than the block_size multipled by how many blocks there are, which returns a value added by 1. 
*					This ensures that there are correct numbers of allocated blocks. This variable is useful when trying 
*					to display the allocated blocks
*
*	j			--	refers to the variable which will be used in the for loop, it is used to display the whole block 
*					vertically
*	
*	k 			--	refers to the variable which will be used in the for loop, it is used to display the block numbers
*					and indexes of the same values horizontally
*
*	index 		--	this variable holds the current index for the blocks, which is later compared to the tmp->index to 
*					find each value accurately so they can be displayed combining all other variables
*
*	temp_num_blocks 		--	this variable gets a copy of the num_blocks, so it can be changed during manipulation
*								of other variables when trying to display the blocks. It is a handy variable because
*								trying to change the index/tmp->index on it's own proves it harder to do so but using 
*								this variable provies a bit more flexbility because the program can act accoridingly
*
*	current_num_blocks 		--	this variable holds the value of num_blocks. It is used so that each time the num_blocks
*								are displayed in 3, if the num_blocks are greater than 3 then the current_num_blocks will 
*								hold the value of (num_blocks - 3) for num_blocks to take away, so num_blocks constantly
*								gets the value of 3 or less.
*
*	new_level	--	this variable is used if num_blocks was greater than 3, to indicate that a new level is deployed.
*					It is useful to use in an if statement, with the given value 1 to indicate that num_blocks was greater
*					than 3 so a new_level is needed. It is set to 0 once the current level is finished and then later becomes
*					1 or 0 depending on whether num_blocks is still greater than 3 or not.
*
*	count		--	this variable is very useful, as it allows the current stack_int structure to change it's top node
*					to the next depending on how many num_blocks there are. It is useful because each time, it sets the
*					current stack_int structure to the top of the stack in a new level
*
*	display     --  this variable holds the fresh values of num_blocks, which references the descending order of numbers to be
*					used within the display function to indicate which block it refers to. It is constantly updated if num_blocks
*					is greater than 3 so it keeps track of which blocks was which.
*
* Description: 
*
*	This function helps aid the user or other people using the stack library to visually see the manipulation of data 
*   happening, it does not only provide the user with what values are being pushed/popped but it also shows the actual 
*	block sizes, blocks that are allocated, what values are added at which index and clearly outlines which block was the 
*	first block that was allocated and which was the last
*
* **********************************************************************************************************************/

void stack_int_display(stack_int *s){

	assert(s!=NULL);

	stack_int * tmp = (stack_int *)malloc(sizeof(stack_int));		// used as a temporary accessor for the stack
	stack_int * current = (stack_int *)malloc(sizeof(stack_int));	// used to keep track of top of the stack for displaying purposes

	//Values of tmp references the s stack

	tmp->top = s->top;	
	tmp->block_size = s->block_size;
	tmp->stack_size = s->stack_size;
	tmp->index = tmp->block_size;		// this index equals to the block size, so that items start displaying from top to bottom

	current->top = tmp->top;			// becomes the current top block


	int num_blocks = (int)(tmp->stack_size / tmp->block_size), j, k, index, temp_num_blocks, current_num_blocks = 0, new_level = 0, count, display;

	// This block of code checks to see if num_blocks is 1, in this case 0 then add 1 to it
	// else if its more than 1 e.g. 21 items are assigned then it becomes 2 so add 1 to it so its 3
	// because in reality 20 items will be in 2 blocks if max size is 10 for each array and the 1 left over will be in the 3rd block

	if(num_blocks == 0){
		num_blocks = 1;
	}else if((stack_int_size(tmp) > (int)(tmp->block_size * num_blocks))){
		num_blocks += 1;
	}

	display = num_blocks;				// it becomes the current block size, so it can be used to display the current block number in descending order

	// Because we want to show 3 blocks per line, if number of blocks is greater than 3, then the current_num_blocks variable will
	// do the calculation to store the remaining block numbers whilst num_blocks takes away values from current_num_blocks to get 3 as an answer

	if(num_blocks > 3){
		current_num_blocks = num_blocks - 3;
		num_blocks -= current_num_blocks;
	}

	temp_num_blocks = num_blocks;		// temp_num_blocks become the current num_blocks, which will be used later for outputting values
	index = s->index;					// index becomes the current index in the s stack, which is used to compare with tmp->index
	index--;							// we want the index to take away 1 each time to point to the current value in stack


	// if stack is empty then it prints out NULL and free's all allocated spaces
	// else it executes code to display the values

	if(stack_int_isempty(s)){

		printf("\n\t Stack is NULL\n\n");

	}else{

		printf("\n");					// prints new line 

		while(num_blocks != 0){			// checks to see if current num_blocks is equal to 0 or not, if true then exits else execute
			if(num_blocks < 4){			// this verifys that if num_blocks is less than 4 then execute the code to display, in this case
										// it will always execute because it has been declared earlier to always return 3 or less

				for(k=display; k>current_num_blocks; k--){		// this code uses the display variable to display current block number
					printf("\tBlock %d\t\t", k);
				}
				printf("\n\n");

				// this code displays a block vertically
				// takes away 1 from tmp->index each time the for loop runs

				for(j=0; j<tmp->block_size; j++){
					tmp->index--;	

					// this for loop prints horizontally depending on the number of blocks
					// it prints each value for the current index in the different blocks

					for(k=0; k<num_blocks; k++){

						// checks to see if current index matchs tmp->index
						// or temp_num_blocks less than number of blocks
					    // then print else prints empty block

						if(tmp->index == index || temp_num_blocks < num_blocks){
							printf("\tIndex %d [ %2d ]\t", tmp->index, tmp->top->items[tmp->index]);

							// At the beginning we set temp_num_blocks to become num_blocks
							// if they match then we want to take away index by 1 and temp_num_blocks by 1
							// that way each time the loop is running, it can display values correctly for the current block
							// else is shows garbage values

							if(temp_num_blocks == num_blocks){		
								index--;
								temp_num_blocks--; 
							}

							// else if it don't match then print empty values, in this case [ ]
							// if num_blocks is greater than 0, then take away 1 from temp_num_blocks

						}else{
							printf("\tIndex %d [  ]\t", tmp->index);
							if(num_blocks > 0){
								temp_num_blocks--;
							}
						}

						// this allows us to check if current tmp->top is NULL or not
						// if not then change the top to the next block within the same loop to display horizontally the values
						// from each block in the same index

						if(tmp->top != NULL){
							tmp->top = tmp->top->next;
						}
					}

					// once the loop ends, it prints a new line within the vertical block to indicate a new index
					// then checks to see if there is a new level, meaning more than 3 blocks than start a new line
					// if so then tmp->top will become current->top indicating the new top block in the new line
					// else the tmp->top that was the next block within the loop now becomes the top block again

					printf("\n");
					if(new_level == 1){
						tmp->top = current->top;
					}else{
						tmp->top = s->top;
					}	
					temp_num_blocks = num_blocks;
				}
			}

			printf("\n");		// prints a new line, to seperate from the top 3 blocks and start a new line

			count = 0;			// set values of count and new_level to 0
			new_level = 0;

			// this loop indicates that while count is less than the number of blocks then checks
			// if current->top->next equals to NULL or not, if not then current->top becoems next block and so on 
			// until count becomes the same as num_blocks
			// current->top basically refers to the top block within the new line


			while(count < num_blocks){
				if(current->top->next != NULL){
					current->top = current->top->next;
				}
				count++;
			}

			new_level++;		// new_level adds 1 to indicate that the process so far has led to this point
								// so it indicates that there is a new level

			if(current->top != NULL){		// checks to see if current->top equals to NULL or not before appointing
				tmp->top = current->top;	// tmp->top to become the current->top
			}

			num_blocks = current_num_blocks;		// num_blocks changes to current_num_blocks value until it reaches 0
													// or to refer to the number of values in the new line

			display = num_blocks;					// this changes to the current num_blocks to display current number of block
			tmp->index = tmp->block_size;			// sets tmp->index to become max block size, so index starts from top to bottom
			index = tmp->block_size;				// becomes the same as tmp->index for comparing, because the new line is a 
													// continuation of displaying blocks so it display items in the current block
			index--;								// takes away 1 from index because its currently max size


			// if number of blocks is greater than or equal to 3, then the current_num_blocks variable will do the calculation to store 
			// the remaining block numbers whilst num_blocks takes away values from current_num_blocks to get 3 or less as an answer

			if(num_blocks >= 3){
				current_num_blocks = num_blocks - 3;
				num_blocks -= current_num_blocks;
			}

			temp_num_blocks = num_blocks;			// becomes current number of block

			// if num_blocks is less than 3 than we know that there won't be any more 
			// levels/lines of blocks to be displayed, so it sets current_num_blocks to 0, so when 
			// the number of blocks reaches the point where it becomes the value of current_num_blocks
			// then when the while loop checks if current value equals to 0 or not, it can quit/carry on executing

			if(num_blocks < 3){	
				current_num_blocks = 0;	
			}

		}
	}

	free(tmp);										// frees currently allocated spaces
	free(current);

}

/*********************************************************************************************************************** 
*
* void stack_int_release (stack_int *s)
*
* Parameters:
* 
*	*s 			--	this parameter refers to the stack the user will use as an input, it will be used to point to the
*					given stack as a reference
*
* Description: 
*
*	This function releases the referenced stack from the heap, it releases it from being dynamically allocated which
*	free's any space left over after the program is finished being used
*
* **********************************************************************************************************************/

void stack_int_release(stack_int *s){
	assert(s!=NULL);	// checks to see if stack is NULL or not
	free(s);			// frees stack in the memory currently 
}



