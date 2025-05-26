#ifndef _static_stack_H
#define _static_stack_H


#include <stdio.h>
#include <string.h>

#define MAX_SIZE  5

/* section : data type decleration */
typedef unsigned char boolean;
typedef unsigned char uint_8;
typedef unsigned short uint1_16;
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
    sint_32 stack_pointer;
    uint_32 stack_array[MAX_SIZE];
} stack_t;

typedef enum{
    f_ok,
    f_Nok
} return_status_t;

typedef enum{
    stack_empty,
    stack_full,
    stack_not_full
} stack_status_t;

/* section : user defined functions */
return_status_t stack_init(stack_t *my_stack);
return_status_t stack_push(stack_t *myStack, uint_32 Value);
return_status_t stack_pop(stack_t *myStack, uint_32 *Value);
return_status_t stack_top(stack_t *myStack, uint_32 *Value);
return_status_t stack_display(stack_t *myStack);
return_status_t stack_size(stack_t *myStack, uint_32 *size);

#endif

/* functions implementation */

/**
 *@brief  helper function to check if the stack is full
 *@param myStack object you want to check
 *@retval to know if the function running successfully or not
 */
static stack_status_t StackFull(stack_t *myStack){
    if(myStack->stack_pointer == MAX_SIZE - 1){
        return stack_full;
    }
    else{
        return stack_not_full;
    }
}

/**
 *@brief  helper function to check if the stack is empty
 *@param myStack object you want to check
 *@retval to know if the function running successfully or not
 */
static stack_status_t StackEmpty(stack_t *myStack){
    stack_status_t ret = stack_empty;
    if(myStack->stack_pointer == -1){
        ret = stack_empty;
    }
    else{
        ret = stack_not_full;
    }
    return ret;
}

/**
 *@brief  function to make stack
 *@param my_stack passing the object of the struct as reference
 *@retval if the function created successfully or not 
 */
return_status_t stack_init(stack_t *my_stack){
    return_status_t ret = f_Nok;
    if(NULL == my_stack){
        ret = f_Nok;
    }
    else{
        my_stack->stack_pointer = -1;
        ret = f_ok;
    }
    return ret;
}

/**
 * @brief adding element in the stack
 * @param myStack passing the object as reference
 * @param Value the value you want to add
 * @retval to know if the function running successfully or not
 */
return_status_t stack_push(stack_t *myStack,uint_32 Value){
    return_status_t ret = f_Nok;
    stack_status_t status = StackFull(myStack);
    if((NULL == myStack) || (stack_full == status)){
        printf("cant push %i ot the stack as it's full\n", Value);
        ret = f_Nok;
    }
    else{
        (myStack->stack_pointer)++;
        myStack->stack_array[myStack->stack_pointer] = Value;
        printf("%i is pushed to the stack\n", Value);
        ret = f_ok;
    }
    return ret;
}

/**
 * @brief removing element from the stack
 * @param myStack passing the object as reference
 * @param Value the place you want to store the value in
 * @retval to know if the function running successfully or not
 */
return_status_t stack_pop(stack_t *myStack,uint_32 *Value){
    return_status_t ret = f_Nok;
    if((NULL == myStack) || stack_empty == StackEmpty(myStack)){
        printf("ERROR! stack is empty\n");
        ret = f_Nok;
    }
    else{
        *Value = myStack->stack_array[myStack->stack_pointer];
        (myStack->stack_pointer)--;
        printf("%i is popped\n",*Value);
        ret = f_ok;
    }
    return ret;
}

/**
 * @brief to show the last element of the stack
 * @param myStack passing the object as reference
 * @param Value the place you want to store the value in
 * @retval to know if the function running successfully or not
 */
return_status_t stack_top(stack_t *myStack,uint_32 *Value){
    return_status_t ret = f_Nok;
    if((NULL == myStack) || (stack_empty == StackEmpty(myStack))){
        printf("ERROR! stack is empty\n");
        ret = f_Nok;
    }
    else{
        *Value = myStack->stack_array[myStack->stack_pointer];
        ret = f_ok;
    }
    return ret;
}

/**
 * @brief to show the stack elements
 * @param myStack passing the object as reference
 * @retval to know if the function running successfully or not
 */
return_status_t stack_display(stack_t *myStack){
    return_status_t ret = f_Nok;
    sint_32 counter = 0;
    if((NULL == myStack)){
        printf("ERROR!\n");
        ret = f_Nok;
    }
    else{
        if(stack_empty == StackEmpty(myStack)){
            printf("stack is empty\n");
            ret = f_ok;
        }
        else{
            printf("stack data : ");
            for (counter = myStack->stack_pointer; counter >= 0;counter--){
                printf("%i\t", myStack->stack_array[counter]);
            }
            ret = f_ok;
            printf("\n");
        }
    }
    return ret;
}

/**
 * @brief to show the number of elements in the stack
 * @param myStack passing the object as reference
 * @param Value the place you want to store the value in
 * @retval to know if the function running successfully or not
 */
return_status_t stack_size(stack_t *myStack,uint_32 *size){
    return_status_t ret = f_Nok;
    if((NULL == myStack) || (NULL == size)){
        printf("ERROR!\n");
        ret = f_Nok;
    }
    else{
        if(stack_empty == StackEmpty(myStack)){
            *size = 0;
            ret = f_ok;
        }
        else if(stack_full == StackFull(myStack)){
            *size = MAX_SIZE;
            ret = f_ok;
        }
        else{
            *size = (myStack->stack_pointer) + 1;
            ret = f_ok;
        }
    }
    return ret;
}