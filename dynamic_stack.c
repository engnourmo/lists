#ifndef _DYNAMIC_STACK_H
#define _DYNAMIC_STACK_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* section : data type decleration */
typedef unsigned char boolean;
typedef unsigned char uint_8;
typedef unsigned short uint_16;
typedef unsigned int uint_32;
typedef unsigned long long uint_64;
// signed
typedef signed char sint_8;
typedef signed short sint_16;
typedef signed int sint_32;
typedef signed long long sint_64;
// float
typedef float float_32;
typedef double float_64;

typedef struct{
    void **stackArray;
    sint_32 ElementCount;
    uint_32 elementMAxsize;
    sint_32 stacktop;
} stack_t;

typedef enum{
    stack_ok,
    stack_Nok,
    stackFull,
    stcakEmpty,
    stackNullPointer
} stackStatus;

/* section : user defined functions */
stack_t *stack_init(uint_32 stackmaxsize, stackStatus *returnstatus);
stack_t *DestroyStack(stack_t *myStack, stackStatus *returnstatus);
stackStatus pushStack(stack_t *myStack, void *ptr);
stackStatus popStack(stack_t *myStack, void **ptr);
stackStatus topStack(stack_t *myStack, void **ptr);
stackStatus stackCount(stack_t *myStack, uint_32 *size);
stackStatus displayStack(stack_t *myStack);

#endif


static uint_8 StackFull(stack_t *myStack){
    return (myStack->ElementCount == myStack->elementMAxsize);
}

static uint_8 StackEmpty(stack_t *myStack){
    return (myStack->ElementCount == 0);
}

/**
  * @brief  This algorithm creates an empty stack by allocating the head
            structure and the array from dynamic memory.
  * @param stackmaxsize  Stack maximum number of elements
  * @param returnstatus  Status returned while performing this operation
  * @retval Pointer to the allocated stack in the heap
  */
stack_t *stack_init(uint_32 stackmaxsize,stackStatus *returnstatus){
    stack_t *myStack = NULL;
    if(NULL == returnstatus){
        myStack = NULL;
        *returnstatus = stackNullPointer;
    }
    else{
        myStack = (stack_t *)malloc(sizeof(stack_t));
        if(NULL == myStack){
            *returnstatus = stack_Nok;
        }
        else{
            myStack->stacktop = -1;
            myStack->ElementCount = 0;
            myStack->elementMAxsize = stackmaxsize;
            myStack->stackArray = (void **)calloc(myStack->elementMAxsize, sizeof(void *));
            if(NULL == myStack->stackArray){
                free(myStack);
                *returnstatus = stack_Nok;
            }
            else{
                *returnstatus = stack_ok;
            }
        }
    }
    return myStack;
}

/**
  * @brief  This function releases all memory to the heap.
  * @param myStack pointer to stack head structure
  * @param returnstatus Status returned while performing this operation
  * @retval NULL
  */
stack_t *DestroyStack(stack_t *myStack,stackStatus *returnstatus){
    if((NULL == myStack) || (NULL == returnstatus)){
        *returnstatus = stackNullPointer;
    }
    else{
        free(myStack->stackArray);
        free(myStack);
        *returnstatus = stack_ok;
    }
    return NULL;
}

/**
  * @brief This function pushes an item onto the stack.
  * @param myStack pointer to stack head structure
  * @param ptr pointer to be inserted
  * @retval Status returned while performing this operation
  */
stackStatus pushStack(stack_t *myStack,void *ptr){
    stackStatus ret = stack_Nok;
    if((NULL == myStack) || (NULL == ptr)){
        ret = stackNullPointer;
    }
    else{
        if(StackFull(myStack)){
            ret = stackFull;
        }
        else{
            (myStack->stacktop)++;
            myStack->stackArray[myStack->stacktop] = ptr;
            (myStack->ElementCount)++;
            ret = stack_ok;
            printf("element is pushed\n");
        }
    }
    return ret;
}

/**
  * @brief This function pops the item on the top of the stack.
  * @param myStack pointer to stack head structure
  * @param ptr return the Value that have been popped
  * @retval Status returned while performing this operation
  */
stackStatus popStack(stack_t *myStack,void **ptr){
    stackStatus ret = stack_Nok;
    if((NULL == myStack) || (NULL == ptr)){
        ret = stackNullPointer;
    }
    else{
        if(StackEmpty(myStack)){
            ret = stcakEmpty;
        }
        else{
            *ptr = myStack->stackArray[myStack->stacktop];
            (myStack->stacktop)--;
            (myStack->ElementCount)--;
            ret = stack_ok;
            printf("element is popped\n");
        }
    }
    return ret;
}

/**
  * @brief  This function retrieves the data from the top of the
            stack without changing the stack.
  * @param myStack pointer to stack head structure
  * @param ptr eturn the Value of last element
  * @retval Status returned while performing this operation
  */
stackStatus topStack(stack_t *myStack,void **ptr){
    stackStatus ret = stack_Nok;
    if((NULL == myStack) || (NULL == ptr)){
        ret = stackNullPointer;
    }
    else{
        if(StackEmpty(myStack)){
            ret = stcakEmpty;
        }
        else{
            *ptr = myStack->stackArray[myStack->stacktop];
            ret = stack_ok;
        }
    }
    return ret;
}

/**
  * @brief  Returns number of elements in stack.
  * @param myStack pointer to stack head structure
  * @param size number of elements in stack.
  * @retval Status returned while performing this operation
  */
stackStatus stackCount(stack_t *myStack,uint_32 *size){
    stackStatus ret = stack_Nok;
    if((NULL == myStack) || (NULL == size)){
        ret = stackNullPointer;
    }
    else{
        if(StackFull(myStack)){
            *size = myStack->elementMAxsize;
        }
        else if(StackEmpty(myStack)){
            *size = 0;
        }
        else{
            *size = (myStack->stacktop) + 1;
        }
        ret = stack_ok;
    }
    return ret;
}

/**
 * @brief this algorithm displays the elements in the stack
 * @param myStack pointer to stack head structure
 * @retval Status returned while performing this operation
 */
stackStatus displayStack(stack_t *myStack){
    stackStatus ret = stack_Nok;
    sint_32 counter = 0;
    uint_32 *ptr = NULL;
    if(NULL == myStack){
        ret = stackNullPointer;
    }
    else{
        if(StackEmpty(myStack)){
            printf("the stack is empty\n");
            ret = stack_ok;
        }
        else{
            printf("stack items : ");
            for (counter = myStack->stacktop; counter >= 0;counter--){
                ptr = myStack->stackArray[counter];
                printf("%i\t", *ptr);
            }
            printf("\n");
            ret = stack_ok;
        }
    }
    return ret;
}