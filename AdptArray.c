#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct AdptArray_ {
    PElement* array;
    int size;
    COPY_FUNC copy;
    DEL_FUNC del;
    PRINT_FUNC print;
};typedef struct AdptArray_ AdptArray;
typedef struct AdptArray_* PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC del,PRINT_FUNC print){
    PAdptArray adptArray = (PAdptArray)malloc(sizeof(struct AdptArray_));
    if(adptArray == NULL){
        return NULL;
    }
    adptArray->array = NULL;
    adptArray->size = 0;
    adptArray->copy = copy;
    adptArray->del = del;
    adptArray->print = print;
    return adptArray;
}

void DeleteAdptArray(PAdptArray adptArray){
    if(adptArray == NULL){
        return;
    }
    for(int i = 0; i < adptArray->size; i++){
        if(adptArray->array[i] != NULL){
            adptArray->del(adptArray->array[i]);
        }
    }
    free(adptArray->array);
    free(adptArray);
}
Result SetAdptArrayAt(PAdptArray adptArray, int index, PElement element){
    if(adptArray == NULL || index < 0 || element == NULL){
        return FAIL;
    }
    if(index >= adptArray->size){
        PElement *newArray = (PElement*)calloc(index+1, sizeof(PElement));
        if(newArray == NULL){
            return FAIL;
        }
        for(int i = 0; i < adptArray->size; i++){
            newArray[i] = adptArray->array[i];
        }
        free(adptArray->array);
        adptArray->array = newArray;
    adptArray->size = index+1;
    }
    if(adptArray->array[index] != NULL){
        adptArray->del(adptArray->array[index]);
    }
    adptArray->array[index] = adptArray->copy(element);
    return SUCCESS;
}
PElement GetAdptArrayAt(PAdptArray adptArray, int index){
    if(adptArray == NULL || index < 0 || index >= adptArray->size){
        return NULL;
    }
    if(adptArray->array[index] == NULL){
        return NULL;
    }
    PElement element = adptArray->copy(adptArray->array[index]);
    return element;
}
int GetAdptArraySize(PAdptArray adptArray){
    if(adptArray == NULL){
        return -1;
    }
    return adptArray->size;
}
void PrintDB(PAdptArray adptArray){
    if(adptArray == NULL){
        return;
    }
    for(int i = 0; i < adptArray->size; i++){
        if(adptArray->array[i] == NULL){
            continue;
        }
        adptArray->print(adptArray->array[i]);
    }
}