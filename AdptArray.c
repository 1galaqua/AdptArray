#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"



typedef struct AdptArray_ 
{
    int size;           
    PRINT_FUNC print;      // print function 
    COPY_FUNC copy;        // copy function 
    DEL_FUNC delete;          // delete function 
    PElement *data;        //  pointers Array
} AdptArray;

   // new adapter array with the function copy and delete and print
PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC delete, PRINT_FUNC print) {
    PAdptArray arr = (PAdptArray)malloc(sizeof(AdptArray));
    if (arr == NULL)
        {  //check if the malloc success
        return NULL;
        }

        // set deafult data 
        arr->size = 0;
        arr->data = NULL;
        //set the function of the adpter Array
        arr->copy = copy;
        arr->delete = delete;
        arr->print = print;
        return arr;
}

// delete all element from the adapter Array
void DeleteAdptArray(PAdptArray arr) {

    if (arr == NULL)
    {// if null jusr return
        return;
    }
    if (arr->data != NULL) {//if have elemets in the array
        for (int i = 0; i < arr->size; i++) 
        { 
            if (arr->data[i] != NULL)
            {//if the specified index is not null we operate on it the delete function
                arr->delete(arr->data[i]);
                
            }
            
        }
        
        free(arr->data);//free the data 
    }
    
    free(arr);//free the adapter
}

// in the adapter array  set the element in the specified index
Result SetAdptArrayAt(PAdptArray arr, int index, PElement element) {

    if (index < 0) 
    {//if the index is not positive then failed
        //printf("negative index\n");
        return FAIL;
    }

    // resize the array if its not big enough
    if (index >= arr->size)
    {
        int new_size = (index + 1);

        PElement* new_arr = (PElement*)realloc(arr->data, new_size * sizeof(PElement));// reallocated a new array with the new size
        if (new_arr == NULL) 
        {
            //printf("failed to resize array\n");
            return FAIL;
        }

        for (int i = arr->size; i < new_size; i++)
        {// initialize the new elements in the array to NULL
            new_arr[i] = NULL;
        }

        arr->data = new_arr;
        arr->size = new_size;
    }

    // copy the element into the array
    PElement new_element = arr->copy(element);

    if (new_element == NULL)
    {
        // printf("failed copy\n");
        return FAIL;
    }

    PElement old_element = arr->data[index];

    if (old_element != NULL) 
    {
        arr->delete(old_element);// delete old
        
        return FAIL;
    }
     
    arr->data[index] = new_element;
    return SUCCESS;
}


   // get the element at the specified index
PElement GetAdptArrayAt(PAdptArray arr, int index) {

    if (arr == NULL || index < 0 || index >= arr->size)
    { //check if array is nuul or index is negetive or index is out of bounds 
        return NULL;
    }

    if(arr->data[index]!=NULL)
    {//if have element in index  we return the copy of this elements by operate on it the copy function 
        return arr->copy(arr->data[index]);
    }

    return NULL;
}

  // get the size of the adapter array
int GetAdptArraySize(PAdptArray arr) {
    if (arr == NULL)
    {
        return 0;
    }

    return arr->size;// return the size
}

// print all of the adapter array
void PrintDB(PAdptArray arr) {
    if (arr == NULL)
    {
        return;
    }

    for (int i = 0; i < arr->size; i++) 
    {
        
        if (arr->data[i] != NULL) 
        {//if the specified index not null operate the print function on it.
        
            arr->print(arr->data[i]);
        }
    }
}
//I used two PDF files:
//1) There was a practice summary (from systems programming 1) that had explanations about ADPT
//2) General summary of the C language
//and a YouTube video:
//https://www.youtube.com/watch?v=6Ir4l0VuI7Y&t=518s&ab_channel=CodeVault