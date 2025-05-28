#include <stdio.h>
#include <string.h>
#include "test1.h"

sint_32 LinearSearch(uint_32 arr[],uint_32 length,uint_32 value){
    uint_32 counter = 0;
    for (counter = 0; counter < length;counter++){
        if(value == arr[counter]){
            return counter;
            break;
        }
        else{

        }
    }
    return -1;
}

sint_32 binarysearch(uint_32 arr[],uint_32 sIndex,uint_32 eIndex,uint_32 value){
    uint_32 Index = 0;
    while(sIndex <= eIndex){
        Index = sIndex + ((eIndex - sIndex) / 2);
        if(value == arr[Index]){
            return Index;
            break;
        }
        else if(value > arr[Index]){
            sIndex = Index + 1;
        }
        else{
            eIndex = Index - 1;
        }
    }
    return -1;
}