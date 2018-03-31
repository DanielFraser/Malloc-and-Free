#include <stdio.h>
#include <stdlib.h>

#define malloc( x ) myMalloc( x, __FILE__, __LINE__ )
#define free( x ) myFree( x, __FILE__, __LINE__ )

/*
 * the struct to hold the meta data
 */
typedef struct
{
	size_t size : 13; //size of bytes of the block using 13 bits (excluding size of the struct itself)
	int is_free : 2; //only use 2 bits for boolean value
    struct metaStruct * next; //points to the next meta data inside the memory block
}metaStruct;

/*
 * Function declarations for mymalloc.c
 */
void* myMalloc(size_t numBytes, char* fileName, int lineNumber);
void myFree(void* pointer, char* fileName, int lineNumber);
void * splitBlocks(metaStruct* , size_t);
void mergeBlocks();

/*
 * used to tell memgrind.c if memory is full or not
 *
 * 0 - memory should have room for more malloc()s
 * 1 - memory is full
 */
int memoryFull;
