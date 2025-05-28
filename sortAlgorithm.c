#include <stdio.h>
#include <string.h>
#include "test1.h"


static void swapF(uint_32 *num1,uint_32 *num2){
    uint_32 tempnum = *num1;
    *num1 = *num2;
    *num2 = tempnum;
}

void bubbleSortF(uint_32 arr[],uint_32 length){
    uint_32 counter = 0, counter2 = 0;
    uint_32 flag = 0; //for chaeck adaptivity
    for (counter = 0; counter < length - 1;counter++){
        for (counter2 = 0; counter2 < length - 1 - counter;counter2++){
            if(arr[counter2] > arr[counter2 + 1]){
                swapF(&arr[counter2], &arr[counter2 + 1]);
                flag = 1;
            }
        }
        if(0 == flag){
            return;
        }
    }
}

void isertionSortF(uint_32 arr[],uint_32 length){
    uint_32 key = 0,counter = 0, counter2 = 0;
    for (counter = 1; counter < length;counter++){
        key = arr[counter];
        counter2 = counter - 1;
        while((key < arr[counter2]) && (counter2 >=0)){
            arr[counter2 + 1] = arr[counter2];
            counter2--;
        }
        arr[counter2 + 1] = key;
    }
}