#include "Stack.h"
#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
#include <stdlib.h> 

/******
 * In this file, provide all of the definitions of the stack functions as described in stack.h.
 *
 * ****/


Stack newStack(int maxSize){

	// Initializing the array of stacks with malloc.
	Stack s = (Stack*) malloc(sizeof(Stack)); 

	if (!s) return 0;

	s->count = -1; 
	s->maxSize = maxSize; 

	//mallocing the stackElements array.
	s->stackElements = (int*) malloc(maxSize * sizeof(int)); 

	if (!s->stackElements) return 0;

	return s;

}

//Free stack to free both StackImp and stackElements arrays.
void freeStack(Stack s){

	free(s->stackElements);
	free(s);

}


//push an ele4ment to stack.
void push(Stack s, char e){

	s->stackElements[++s->count] = e;

}


//Pop an element from stack.
char pop(Stack s){

	if (!isEmpty(s)) 
		return s->stackElements[s->count--] ; 


}

//Check if stack is empty 
int isEmpty(Stack s){

	return s->count == -1;


}


// Return the top element in the stack.
char topElement(Stack s){

	return s->stackElements[s->count];

}
