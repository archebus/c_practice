#include <stdio.h>
#include <stdlib.h>

typedef struct dArray {
    int* data;
    int size;
    int capacity;
} dArray;

// Pass c to create a dynamic array with c capacity. Returns pointer to the dynamic array.
dArray* createDynamicArray(int c) {

    // Memory assignment.
    dArray* array = malloc(sizeof(dArray));
    array->data = malloc(c * sizeof(int));
    
    // Defense against failed malloc.
    if (array == NULL || array->data == NULL) {
        printf("Memory allocation failed.\n");
        free(array->data);
        free(array);
        return NULL;
    }

    // Prop init.
    array->size = 0;
    array->capacity = c;

    // Return pointer.
    return array;
}

// Will safely add data to end of the array, pass pointer to array and the data to be appended.
void append(dArray* array, int d) {
    
    // Make sure array can fit new elements.
    if (array->size == array->capacity) {
        int newCapacity = array->capacity * 2;
        int* newData = malloc(newCapacity * sizeof(int));

        // Defense against failed malloc.
        if (newData == NULL) {
            printf("Memory allocation failed.\n");
            free(newData);
            return;
        }

        // Move old array data to new location.
        for (int i = 0; i < array->size; i++) {
            newData[i] = array->data[i];
        }

        // Cleanup mem and prop pointers.
        free(array->data);
        array->data = newData;
        array->capacity = newCapacity;

    }

    // Update instance props.
    array->data[array->size] = d;
    array->size++;
}

// Gets value at index i.
int get(dArray* array, int index) {

    // Defense against pushing index out of bounds.
    if (index < 0 || index >= array->size) {
        printf("Index out of bounds.\n");
        return 0;
    }

    return array->data[index];
}

// Set a new value at a specific index.
void set(dArray* array, int index, int d) {

    // Defense against pushing index out of bounds.
    if (index < 0 || index >= array->size) {
        printf("Index out of bounds.\n");
        return;
    }

    // Overwrite value at that index.
    array->data[index] = d;

}

// Returns a dArrays size (number of data elements).
int getSize(dArray* array) {
    return array->size;
}

// Returns a dArrays capacity (availabe space for elements).
int getCapacity(dArray* array) {
    return array->capacity;
}

// Safely remove value at index and shift elements.
void removeAt(dArray* array, int index) {
    
    // Defense against pushing index out of bounds.
    if (index < 0 || index >= array->size) {
        printf("Index out of bounds.\n");
        return;
    }

    // Start at index, and work through remainder of array (for values shift).
    for (int i = index; i < array->size -1; i++) {
        array->data[i] = array->data[i + 1];
    }

    // Decrement size.
    array->size--;
}

// Encapsulated memory cleanup into a single function.
void freeDynamicArray(dArray* array) {
    free(array->data);
    free(array);
}


int main() {

    dArray* myArray = createDynamicArray(10);

    for (int i=0; i<20; i++) {
        append(myArray, i);
    }

    set(myArray, 10, 1000);

    removeAt(myArray, 10);

    printf("Data: %d\n",get(myArray, 4));
    printf("Data: %d\n",get(myArray, 10));
    printf("Size: %d\n",myArray->size);

    freeDynamicArray(myArray);

    return 0;

}