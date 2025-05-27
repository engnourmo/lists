#ifndef _TEST1_H
#define _TEST1_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE  5

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
    void **queueArray;
    uint_32 elementmaxsize;
    uint_32 elementcount;
    sint_32 queuerear;
    sint_32 queuefront;
} queue_t;

typedef enum{
    queueFull,
    queueEmpty,
    queue_OK,
    queue_NOK,
    queueNullPointer,
} queue_status_t;

/* section : user defined functions */
queue_t *creatqueue(uint_32 size, queue_status_t *returnstatus);
queue_t *destroyqueue(queue_t *myqueue, queue_status_t *returnstaus);
queue_status_t enqueueF(queue_t *myqueue, void *number);
queue_status_t dequeueF(queue_t *myqueue, void **ptr);
queue_status_t queuefront(queue_t *myqueue, void **ptr);
queue_status_t queuerear(queue_t *myqueue, void **ptr);
queue_status_t queuecount(queue_t *myqueue, uint_32 *size);

#endif


static uint_32 QueueFull(queue_t *myqueue){
    return (myqueue->elementmaxsize == myqueue->elementcount);
}

static uint_32 QueueEmpty(queue_t *myqueue){
    return (myqueue->elementcount == 0);
}

queue_t *creatqueue(uint_32 size,queue_status_t *returnstatus){
    queue_t *myqueue = NULL;
    if(NULL == returnstatus){
        myqueue = NULL;
        *returnstatus = queueNullPointer;
    }
    else{
        myqueue = (queue_t *)malloc(sizeof(queue_t));
        if(NULL == myqueue){
            *returnstatus = queueNullPointer;
            myqueue = NULL;
        }
        else{
            myqueue->queueArray = (void **)calloc(myqueue->elementmaxsize, sizeof(void *));
            if(NULL == myqueue->queueArray){
                free(myqueue);
                *returnstatus = queue_NOK;
            }
            else{
                *returnstatus = queue_OK;
                myqueue->elementcount = 0;
                myqueue->elementmaxsize = size;
                myqueue->queuefront = -1;
                myqueue->queuerear = -1;
            }
        }
    }
    return myqueue;
}

queue_t *destroyqueue(queue_t *myqueue,queue_status_t *returnstaus){
    if((NULL == myqueue) || (NULL == returnstaus)){
        *returnstaus = queueNullPointer;
    }
    else{
        free(myqueue->queueArray);
        free(myqueue);
        *returnstaus = queue_OK;
    }
    return NULL;
}

queue_status_t enqueueF(queue_t *myqueue,void *number){
    queue_status_t ret = queue_NOK;
    if((NULL == myqueue) || (NULL == number)){
        ret = queueNullPointer;
    }
    else{
        if(QueueFull(myqueue)){
            ret = queueFull;
            printf("can't add element\n");
        }
        else if(QueueEmpty(myqueue)){
            myqueue->queuefront++;
            myqueue->queuerear++;
            myqueue->elementcount++;
            myqueue->queueArray[myqueue->queuerear] = number;
            ret = queue_OK;
            printf("element added\n");
        }
        else{
            if(myqueue->queuerear == (myqueue->elementmaxsize) - 1){
                myqueue->queuerear = 0;
                myqueue->elementcount++;
                myqueue->queueArray[myqueue->queuerear] = number;
                ret = queue_OK;
                printf("elment added\n");
            }
            else{
                myqueue->queuerear++;
                myqueue->elementcount++;
                myqueue->queueArray[myqueue->queuerear] = number;
                ret = queue_OK;
                printf("elemnt added\n");
            }
        }
    }
    return ret;
}

queue_status_t dequeueF(queue_t *myqueue,void **ptr){
    queue_status_t ret = queue_NOK;
    if((NULL == myqueue) || (ptr == NULL)){
        ret = queueNullPointer;
    }
    else{
        if(QueueEmpty(myqueue)){
            ret = queueEmpty;
            myqueue->queuefront = -1;
            myqueue->queuerear = -1;
            printf("queue is empty\n");
        }
        else{
            if(myqueue->queuefront == (myqueue->elementmaxsize)){
                myqueue->queuefront = 0;
                *ptr = myqueue->queueArray[myqueue->queuefront];
                myqueue->elementcount--;
                ret = queue_OK;
                printf("elment is dequeued\n");
            }
            else{
                *ptr = myqueue->queueArray[myqueue->queuefront];
                myqueue->queuefront++;
                myqueue->elementcount--;
                ret = queue_OK;
                printf("element is dequeued\n");
            }
        }
    }
    return ret;
}

queue_status_t queuefront(queue_t *myqueue,void **ptr){
    queue_status_t ret = queue_NOK;
    if((NULL == myqueue) || (ptr == NULL)){
        ret = queueNullPointer;
    }
    else{
        if(QueueEmpty(myqueue)){
            ret = queueEmpty;
            printf("queue is empty\n");
        }
        else{
            *ptr = myqueue->queueArray[myqueue->queuefront];
            ret = queue_OK;
        }
    }
    return ret;
}

queue_status_t queuerear(queue_t *myqueue,void **ptr){
    queue_status_t ret = queue_NOK;
    if((NULL == myqueue) || (ptr == NULL)){
        ret = queueNullPointer;
    }
    else{
        if(QueueEmpty(myqueue)){
            ret = queueEmpty;
            printf("queue is empty\n");
        }
        else{
            *ptr = myqueue->queueArray[myqueue->queuerear];
            ret = queue_OK;
        }
    }
    return ret;
}

queue_status_t queuecount(queue_t *myqueue,uint_32 *size){
    queue_status_t ret = queue_NOK;
    if((NULL == myqueue) || (NULL == size)){
        ret = queueNullPointer;
    }
    else{
        if(QueueFull(myqueue)){
            *size = myqueue->elementmaxsize;
            ret = queue_OK;
        }
        else if(QueueEmpty(myqueue)){
            *size = 0;
            ret = queue_OK;
        }
        else{
            *size = myqueue->elementcount;
            ret = queue_OK;
        }
    }
    return ret;
}