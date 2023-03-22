#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
//build the struct
struct AdptArray_ {
    PElement* array;
    int size;
    COPY_FUNC copy;
    DEL_FUNC del;
    PRINT_FUNC print;
};typedef struct AdptArray_ AdptArray;
typedef struct AdptArray_* PAdptArray;
//create the array
PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC del,PRINT_FUNC print){
    //memory allocation for the array
    PAdptArray adptArray = (PAdptArray)malloc(sizeof(struct AdptArray_));
    if(adptArray == NULL){
        return NULL;
    }
    //initalize the array
    adptArray->array = NULL;
    adptArray->size = 0;
    adptArray->copy = copy;
    adptArray->del = del;
    adptArray->print = print;
    return adptArray;
}
//delete the array and free the memory
void DeleteAdptArray(PAdptArray adptArray){
    if(adptArray == NULL){
        return;
    }
    //pass on the array and delete the elements
    for(int i = 0; i < adptArray->size; i++){
        if(adptArray->array[i] != NULL){
            adptArray->del(adptArray->array[i]);
        }
    }
    //free the array
    free(adptArray->array);
    //free the struct
    free(adptArray);
}
//set the elements in the array
Result SetAdptArrayAt(PAdptArray adptArray, int index, PElement element){
    if(adptArray == NULL || index < 0 || element == NULL){
        return FAIL;
    }
    if(index >= adptArray->size){
        //create a new array with the size of the index+1
        PElement *newArray = (PElement*)calloc(index+1, sizeof(PElement));
        if(newArray == NULL){
            return FAIL;
        }
        //pass on the array and copy the elements
        for(int i = 0; i < adptArray->size; i++){
            newArray[i] = adptArray->array[i];
        }
        //free the old array
        free(adptArray->array);
        adptArray->array = newArray;
    adptArray->size = index+1;
    }
    if(adptArray->array[index] != NULL){
        adptArray->del(adptArray->array[index]);
    }
    //copy the element to the array
    adptArray->array[index] = adptArray->copy(element);
    return SUCCESS;
}

//get the element from the array
PElement GetAdptArrayAt(PAdptArray adptArray, int index){
    if(adptArray == NULL || index < 0 || index >= adptArray->size){
        return NULL;
    }
    if(adptArray->array[index] == NULL){
        return NULL;
    }
    //copy the element
    PElement element = adptArray->copy(adptArray->array[index]);
    return element;
}
//get the size of the array
int GetAdptArraySize(PAdptArray adptArray){
    if(adptArray == NULL){
        return -1;
    }
    return adptArray->size;
}
//print function
void PrintDB(PAdptArray adptArray){
    if(adptArray == NULL){
        return;
    }
    //pass on the array and print the elements
    for(int i = 0; i < adptArray->size; i++){
        if(adptArray->array[i] == NULL){
            continue;
        }
        //print the element
        adptArray->print(adptArray->array[i]);
    }
}
