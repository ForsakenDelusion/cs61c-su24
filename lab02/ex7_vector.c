/* Include the system headers we need */
#include <stdlib.h>
#include <stdio.h>

/* Include our header */
#include "ex7_vector.h"

/* Define what our struct is */
struct vector_t {
    size_t size;
    int *data;
};

/* Utility function to handle allocation failures. In this
   case we print a message and exit. */
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

/* Bad example of how to create a new vector */
vector_t *bad_vector_new() {
    /* Create the vector and a pointer to it */
    vector_t *retval, v;
    retval = &v;

    /* Initialize attributes */
    retval->size = 1;
    retval->data = malloc(sizeof(int));
    if (retval->data == NULL) {
        allocation_failed();
    }

    retval->data[0] = 0;
    return retval;
}

/* Create a new vector with a size (length) of 1 and set its single component to zero... the
   right way */
/* TODO: uncomment the code that is preceded by // */
vector_t *vector_new() {
    /* Declare what this function will return */
     vector_t *retval;

    /* First, we need to allocate memory on the heap for the struct */
    retval = malloc(sizeof(vector_t));

    /* Check our return value to make sure we got memory */
    if (retval == NULL) {
        free(retval);
        allocation_failed();
    }

    /* Now we need to initialize our data.
       Since retval->data should be able to dynamically grow,
       what do you need to do? */
    retval->size = 0;
    retval->data = malloc(sizeof(int));

    /* Check the data attribute of our vector to make sure we got memory */
    if (retval->data == NULL) {
        free(retval->data);	//Why is this line necessary?
        allocation_failed();
    }

    /* Complete the initialization by setting the single component to zero */
    retval->data[0] = 0;

    /* and return... */
    return retval; /* UPDATE RETURN VALUE */
}

/* Return the value at the specified location/component "loc" of the vector */
int vector_get(vector_t *v, size_t loc) {

    /* If we are passed a NULL pointer for our vector, complain about it and exit. */
    if(v == NULL) {
        fprintf(stderr, "vector_get: passed a NULL vector.\n");
        abort();
    }

    /* If the requested location is higher than we have allocated, return 0.
     * Otherwise, return what is in the passed location.
     */
    /* YOUR CODE HERE */
    if (loc < v->size) {
        return v->data[loc];   
    }

    return 0;
}

/* Free up the memory allocated for the passed vector.
   Remember, you need to free up ALL the memory that was allocated. */
void vector_delete(vector_t *v) {
    /* YOUR CODE HERE */
    free(v->data);//先释放data，想想为什么?
    free(v);
}

/* Set a value in the vector, allocating additional memory if necessary. 
   If the extra memory allocation fails, call allocation_failed(). */
void vector_set(vector_t *v, size_t loc, int value) {
    /* What do you need to do if the location is greater than the size we have
     * allocated?  Remember that unset locations should contain a value of 0.
     */

    /* YOUR CODE HERE */
     if (loc >= v->size) {
        /* 分配足够的内存以容纳新的位置，所有未设置的位置将被初始化为0 */
        int *new_data = (int *)realloc(v->data, (loc + 1) * sizeof(int));
        if (new_data == NULL) {
            allocation_failed();
        }
        
        /* 初始化新分配的内存 */
        for (size_t i = v->size; i < loc; ++i) {
            new_data[i] = 0;
        }
        
        /* 设置新值 */
        new_data[loc] = value;
        
        /* 更新vector结构体 */
        v->data = new_data;
        v->size = loc + 1; // 更新size为新的最大索引+1
    } else {
        /* 如果位置小于当前大小，直接设置值 */
        v->data[loc] = value;
    }
    
}
