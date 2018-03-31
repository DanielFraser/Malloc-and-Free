#include "mymalloc.h"

static char memoryBlock[5000]; //5000 byte block
static metaStruct * firstMeta = (metaStruct*) &memoryBlock[0]; //first meta data starts at beginning of block

/*
 * Function: myMalloc
 *-----------------------
 *   Givers user memory inside the memory block to be used for what they want
 *   while keeping some memory for metadata (metadata is just before the used memory)
 *
 *   Called by: memgrind.c
 *
 *   input: number of bytes requested, file name and line number called at
 *
 *   returns: a void pointer to free memory (so user can cast pointer to what they need)
 */
void* myMalloc(size_t numBytes, char* fileName, int lineNumber)
{
	void* pointer = NULL; //pointer to return

	if((firstMeta -> size) < 1) //if our first metaBlock is uninitialized (it checks this by checking its size, since this block should have a size greater than 1)
	{
        firstMeta -> next = NULL; //currently the only memory block
        firstMeta -> is_free = 1; //currently the block is being used
        firstMeta -> size = 5000-sizeof(metaStruct); //the block is the size the remaining memory
        memoryFull = 0; //tell us there should be room for more malloc()s
	}
    //search for free memory first
    int foundFreeSpace = 0; //tells if we found an empty block big enough for requested bytes
    metaStruct * cursor = firstMeta; //start at the first block of memory
    while(cursor != NULL && !foundFreeSpace) //find an empty memory slot if possible
    {
        if(cursor -> is_free) //current metadata is free
        {
            pointer = splitBlocks(cursor, numBytes); //checks if we can reuse our current block
            if(pointer) //if we can use this metadata
            {
                memoryFull = 0; //tells the program we were able to find a spot for the bytes requested
                foundFreeSpace = 1; //we found a spot, exit the while loop
            }
        }
        cursor = (metaStruct*) cursor -> next; //move cursor along the meta data
    }
    if(!foundFreeSpace) //if no current metadata is available
    {
        //tell user what happened and why myMalloc() didn't work
        printf("Error: Unable to allocate memory on line %d file %s \n",lineNumber,fileName);
        memoryFull = 1; //tells the program were out of memory, and need to free pointers instead (used for test cases C, D, and F)
        return NULL; //no valid pointer to return so we return NULL
    }
    return pointer; //return pointer to memory just after the metadata
}

/*
 * Function: splitBlocks
 *-----------------------
 *   splits memory blocks that are free so they can be used by other pointers
 *   also checks if the memory is the exact size requested by the user
 *
 *   Called by: myMalloc()
 *
 *   input: address of the pointer to the memory block and bytes requested
 *
 *   returns: a void pointer to free memory (or NULL if it can't be split)
 */
void * splitBlocks(metaStruct* metaBlock, size_t numBytes)
{
    if((metaBlock -> size) == numBytes) //if metadata is the same size, put it in use
    {
        metaBlock -> is_free = 0; //tells the program this metadata is being used
        return (void*) (metaBlock+1); //points to just after the metadata cursor is pointing to
    }
    if((metaBlock-> size) > (numBytes + sizeof(metaStruct))) //if the size of the block can be split into 2
    {
        metaStruct * newMeta = (metaStruct *) ((char*)metaBlock + numBytes + sizeof(metaStruct)); //point to area after end of metaBlock's data

        newMeta -> next = metaBlock -> next; //gets place in between metaBlock's and what it pointed to
        newMeta -> is_free = 1; //new metadata is free to use
        newMeta -> size = (metaBlock -> size) - numBytes - sizeof(metaStruct); //size of the remaining memory after subtracting sizeof(metaStruct)

        metaBlock -> next = (struct metaStruct*) newMeta; //
        metaBlock -> size = numBytes; //newBlock is now size the user requested
        metaBlock -> is_free = 0; //tells the program this metadata is being used
        return (void*) (++metaBlock); //return pointer to just after metadata
    }
    return NULL; //return NULL if unable to split blocks
}

/*
 * Function: mergeBlocks
 *-----------------------
 *   Starts at first metadata block, when it hits a free metadata block, it tries to combine it
 *   with the meta data its pointing to (only if it's free)
 *   it tries to merge consecutive blocks that are free
 *
 *   Called by: myFree()
 *
 *   input: nothing
 *
 *   returns: nothing
 */
void mergeBlocks()
{
    metaStruct * cursor = firstMeta; //starts at the beginning of the linked list of metadata
    metaStruct * cursorNext = NULL; //temporaily stores cursor's next so we can go to it's next
    while(cursor && (cursor -> next)) //while cursor exists and has a next as well
    {
        cursorNext = (metaStruct*) cursor -> next; //holds what the cursor points to
        if((cursorNext -> is_free) && (cursor -> is_free)) //if cursor and it's next is free
        {
            cursor -> size += (cursorNext -> size) + sizeof(metaStruct); //increase size of metadata to the metadatas size and size of struct
            cursor -> next = cursorNext -> next; //point metadata to what it's next pointed to
        }
        else
        {
            cursor = (metaStruct*) cursor -> next; //move next cursor along as well
        }
    }
}

/*
 * Function: myFree
 *-----------------------
 *   Free's each metadata by setting its free flag to 1
 *   first check if its a pointer that we can even free
 *   if it is, then we first check if its already free
 *   if it hasn't been freed yet, we set it to free and call mergeBlocks()
 *
 *   Called by: memgrind.c
 *
 *   input: a pointer to attempt to free, the file name, and line number called at
 *
 *   returns: nothing
 */
void myFree(void *pointer, char* fileName, int lineNumber)
{
    //make sure this pointer is a valid pointer to free
    if((char*)pointer < &memoryBlock[0] || (char*)pointer > &memoryBlock[4999] || pointer == NULL)
    {
        //show error
        printf("Error: Invalid pointer on line %d file %s \n", lineNumber, fileName);
    }
    else
    {
        metaStruct * cursor = (metaStruct *) (pointer); //turn pointer into metaStruct
        --cursor; //get to the metadata of the pointer
        if(cursor -> is_free) //if pointer is already free, print out the error
        {
            //tell user this pointer is already free, and is not allowed to be free again
            printf("Error: Pointer is already free, on line %d file %s \n", lineNumber, fileName);

        }
		else //metadata isn't free so we can free it
		{
			cursor -> is_free = 1; //tells us this data can now be used
            memoryFull = 0; //tells the program memory shouldn't be full anymore
			mergeBlocks(); //go through entire meta data and merge all consecutive blocks
		}
    }
}



