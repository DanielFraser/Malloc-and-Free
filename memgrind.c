#include "mymalloc.h"
#include <time.h>

/*
 * Function Declarations
 */
double testCaseA();
double testCaseB();
double testCaseC();
double testCaseD();
double testCaseE();
double testCaseF();
int randomNumber();

int main()
{
	///declaration of counter
	int i = 0;
	//declaration of total times for all 6 testcases
	double total_TestCaseA = 0;
	double total_TestCaseB = 0;
	double total_TestCaseC = 0;
	double total_TestCaseD = 0;
	double total_TestCaseE = 0;
	double total_TestCaseF = 0;

	clock_t begin = clock(); //begin clock counter
	for(i = 0; i < 1; i++)//loop through all testcases for 100 executions
	{
	    printf("run: %d----------------------------------------------------------\n", i+1);
        total_TestCaseA += testCaseA();//continously add the total time of every testcase until
        total_TestCaseB += testCaseB();//execution of all 100 execution are accounted for
        total_TestCaseC += testCaseC();
        total_TestCaseD += testCaseD();
        total_TestCaseE += testCaseE();
        total_TestCaseF += testCaseF();
		printf("end run: %d------------------------------------------------------\n", i+1);
	}
	clock_t end = clock();//end clock counter
	double total_time = (double)(end - begin)/CLOCKS_PER_SEC;//get the total time for all 100 executions of ALL testcases
	double mean_time = (total_time/100.0) * 1000;//calculate mean time

	double avg_testCaseA =  (total_TestCaseA / 100.0) * 1000;//calculate mean time for EACH test case using the variables defined above
	double avg_testCaseB =  (total_TestCaseB / 100.0) * 1000;//converts each from seconds to milliseconds
	double avg_testCaseC =  (total_TestCaseC / 100.0) * 1000;
	double avg_testCaseD =  (total_TestCaseD / 100.0) * 1000;
	double avg_testCaseE =  (total_TestCaseE / 100.0) * 1000;
	double avg_testCaseF =  (total_TestCaseF / 100.0) * 1000;

	printf("Total Average time: %f milliseconds\n", mean_time);//print out in console the mean times for all testcases as well as the total mean time
	printf("Average Test Case A time: %f milliseconds\n", avg_testCaseA);//formatted in milliseconds
	printf("Average Test Case B time: %f milliseconds\n", avg_testCaseB);
	printf("Average Test Case C time: %f milliseconds\n", avg_testCaseC);
	printf("Average Test Case D time: %f milliseconds\n", avg_testCaseD);
	printf("Average Test Case E time: %f milliseconds\n", avg_testCaseE);
	printf("Average Test Case F time: %f milliseconds\n", avg_testCaseF);

    return 0; //program exited without a problem
}
//Test Case A
/*
 * Function: testCaseB
 *-----------------------
 *   Simply mallocs 1000 1-byte pointers than frees the 1000 1-byte pointers
 *
 *   Called by: main()
 *
 *   input: none
 *
 *   returns: execution time to complete the workload
 */
double testCaseA()
{
    printf("Case A starts--------------------------\n");
	clock_t begin = clock();//begin clock counter
    char * tempPointers[1000]; //holds the 1000 pointers
    int i = 0; //variable for the for loops
    for(i = 0; i < 1000; i++)
    {
        tempPointers[i] = (char *) malloc(1); //create 1000 1-byte pointers
    }

    for(i = 0; i < 1000; i++)
    {
        free(tempPointers[i]); //free each of the 1000 1-byte pointers
    }
	clock_t end = clock();//end clock counter
    printf("Case A ends----------------------------\n");
	double total_time = (double)(end - begin)/CLOCKS_PER_SEC;//calculate total time for for that 1 execution of Test Case A
	return total_time;//return var total_time to be used in main
}
//Test Case B
/*
 * Function: testCaseB
 *-----------------------
 *   Simply mallocs a 1-byte pointer than immediately frees it
 *
 *   Called by: main()
 *
 *   input: none
 *
 *   returns: execution time to complete the workload
 */
double testCaseB()
{
	printf("Case B starts--------------------------\n");
	clock_t begin = clock();//begin clock counter
    char * temp = NULL; //temp pointer to malloc() then free()
    int i = 0; //variable for the for loop
    for(i = 0; i < 1000 ; i++)
    {
        temp = (char *) malloc(1); //create 1 byte pointer
        free(temp); //free the 1-byte pointer
    }
	clock_t end = clock();//end clock counter
    printf("Case B ends----------------------------\n");
	double total_time = (double)(end - begin)/CLOCKS_PER_SEC;//calculate total time for that 1 execution of Test Case A
	return total_time;//return var to be used in main
}
//Test Case C
/*
 * Function: testCaseC
 *-----------------------
 *   Chooses between malloc() a 1-byte pointer and free() based on a random number. If not enough memory, it goes right to freeing instead
 *
 *   Called by: main()
 *
 *   input: none
 *
 *   returns: execution time to complete the workload
 */
double testCaseC()
{
	//intialized variables for malloc as well as 1000 1 byte pointers
	size_t mallocsFreed = 0; //how many mallocs we freed
	size_t malloc_Index = 0; //what index do we put the next malloc on
	size_t free_Index = 0; //what index needs to be freed
	int shouldIMalloc = 0; //should I malloc or free?
    char * tempPointers[1000]; //array to hold the 1000 pointer

	//Test Case C
	printf("Case C starts--------------------------\n");
	clock_t begin = clock();//begin clock counter
	while(mallocsFreed < 1000)
	{
        shouldIMalloc = randomNumber(1,2)-1; //generate a random so we know to free or malloc
		if(shouldIMalloc && malloc_Index <= 999  && !memoryFull)
		{
			tempPointers[malloc_Index] = (char*) malloc(1); //create a 1-byte pointer
			if(tempPointers[malloc_Index]) //make sure we got a valid pointer returned
            {
                malloc_Index++; //move on to the next index
            }
		}
		else if((!shouldIMalloc || memoryFull) && free_Index < malloc_Index)
		{
			free(tempPointers[free_Index]); //free pointer at free_index
            free_Index++; //move onto the next index
            mallocsFreed++; //tells the while loop how many mallocs have been freed
		}
	}
	clock_t end = clock();//end clock counter
	printf("Case C ends----------------------------\n");
	double total_time = (double)(end - begin)/CLOCKS_PER_SEC;//calculate run time of testcase execution
	return total_time;//return var to be used in main
}
//Test Case D
/*
 * Function: testCaseD
 *-----------------------
 *   Chooses between malloc()ing an 1-64 byte pointer and free() based on a random number.
 *   If not enough memory, it goes right to freeing instead
 *
 *   Called by: main()
 *
 *   input: none
 *
 *   returns: execution time to complete the workload
 */
double testCaseD()
{
    printf("Case D starts--------------------------\n");
	//Test Case D:
	clock_t begin = clock();//initialize clock counter
	//initialize variables
	int shouldIMalloc = 0; //either malloc a pointer or free it
	int malloc_Allocation = 0; //holds a random number for bytes to malloc
	char * tempPointers[1000]; //array of 1000 pointers
	size_t mallocsFreed = 0; //mallocs we have freed
	int free_Index = 0; //pointer we should free next
	int malloc_Index = 0; //pointer we should malloc next

	while(mallocsFreed < 1000)
	{
		malloc_Allocation = randomNumber(1,64);//random malloc of 1-64 bytes
        shouldIMalloc = randomNumber(1,2)-1;//rand of malloc or free
		if(shouldIMalloc && malloc_Index <= 999 && !memoryFull) //makes sure we don't go past array limits and their is room for more mallocs
		{
			tempPointers[malloc_Index] = (char*) malloc(malloc_Allocation); //create a pointer that points to 1-64 bytes of data
            if(tempPointers[malloc_Index]) //make sure we got a valid pointer returned
            {
                malloc_Index++; //move on to the next index
            }
		}

        //if memory is full or we chose to free pointer (also makes sure we don't free pointers we didn't allocate yet
		else if((!shouldIMalloc || memoryFull) && free_Index < malloc_Index)
		{
			free(tempPointers[free_Index]); //free pointer at free_index
            free_Index++; //move onto the next index
            mallocsFreed++; //tells the while loop how many mallocs have been freed
		}
	}
	clock_t end = clock();//end clock counter
    printf("Case D ends----------------------------\n");
	double total_time = (double)(end - begin)/CLOCKS_PER_SEC;//calculate total runtime of testcase execution
	return total_time;//return var to be used in main
}
//Test Case E
/*
 * Function: testCaseE
 *-----------------------
 *   Tries to break free() by passing in invalid pointers and freeing a valid pointer more than once
 *   (see testcases.txt to see a more detailed description of testcase F)
 *
 *   Called by: main()
 *
 *   input: none
 *
 *   returns: execution time to complete the workload
 */
double testCaseE()
{
	char * tempPointers[200];//200 byte pointers initializes
	int free_Index = 0; //index that is chosen randomly to free
	int totalTimesRan = 0; //total times the while loop ran
	size_t index = 0; //index to malloc then free 10 times
    size_t errorToThrow = 0; //what error should we try to push to free
	clock_t begin = clock();//begin clock counter;
    char ** attemptToFree = NULL; //a pointer to pass to free() to attempt to free
	printf("Case E starts-------------------------\n");

	while(totalTimesRan < 200) //while we ran this loop less than 200 times
    {
        errorToThrow = randomNumber(0,3); //choose which error to try
        switch(errorToThrow) //using errorToThrow, determine what error to throw
        {
            case 0: //attempt to free non pointers
                free_Index = randomNumber(0,999); //a random index to free
                free(&tempPointers[free_Index]); //attempt to free the address of the pointer inside tempPointers
                break;
            case 1: //attempt to free pointer unallocated by myMalloc() (in this case, a random pointer from tempPointers)
                free_Index = randomNumber(0,999); //a random index to free
                attemptToFree = &tempPointers[free_Index]; //set our pointer to the address of the index we chose
                free(attemptToFree); //attempt to free this address
                break;
            case 2: //Redundancy (freeing same pointer more than once)
                tempPointers[index] = malloc(randomNumber(1,128)); //malloc between 1-128 bytes
                int i = 0; //create our variable for our for loop
                for(i = 0; i < 10; i++)
                {
                    free(tempPointers[index]); //attempt to free the same pointer 10 times
                }
                index++; //next time, try the next index
                break;
        }
        totalTimesRan++; //how many times we ran the loop
    }
	printf("Case E ends-----------------------------\n");
	clock_t end = clock();//end clock counter;
	double total_time =(double)(end - begin)/CLOCKS_PER_SEC;//calculate total execution time for testcase E
	return total_time;//returrn var to be used in main

}
//Test Case F
/*
 * Function: testCaseF
 *-----------------------
 *   Tries to oversaturate our memory using techniques from the previous test cases
 *   (see testcases.txt to see a more detailed description of testcase F)
 *
 *   Called by: main()
 *
 *   input: none
 *
 *   returns: execution time to complete the workload
 */
double testCaseF()
{
	clock_t begin = clock();//begin clock counter
	int shouldIMalloc = 0; //tells us if we should malloc or free
	int malloc_Allocation = 0; //how many bytes to allocate to memory
	char * tempPointers[400];//array of 400  pointers
	size_t mallocsFreed = 0; //how many mallocs we freed
	int free_Index = 0; //what index to free next
	int malloc_Index = 0; //what index to malloc next
	char * temp = NULL; //holds a pointer temporary so we can free it right after
    size_t maxOfForLoops = 40; //how many pointers should each for loop inside malloc and free
    size_t maxMallocs = 400; //how many mallocs we want to free and malloc

	printf("Test Case F starts------------------\n");
	while(mallocsFreed < maxMallocs)
	{
        int i = 0; //used for the for loops
		for(i = malloc_Index; i < maxOfForLoops && i < maxMallocs; i++)
		{
		    tempPointers[i] = (char *) malloc(randomNumber(64,256));
            temp = (char *) malloc(randomNumber(64,256));
			free(temp);
			malloc_Index++;
		}
        //attempt to free all pointers created from the other for loop
		for(i = free_Index; i < maxOfForLoops && i < maxMallocs && i < malloc_Index; i++)
		{
			free(tempPointers[i]);
			free_Index++;
			mallocsFreed++;
		}

        shouldIMalloc = randomNumber(1,2)-1; //should I malloc or free

        if(shouldIMalloc && malloc_Index < maxMallocs && !memoryFull)
        {
            malloc_Allocation = randomNumber(1, 1000); //choose how many bytes to malloc
            tempPointers[malloc_Index] = (char*) malloc(malloc_Allocation);
            if(tempPointers[malloc_Index])
            {
                malloc_Index++;
            }
        }
        else if((!shouldIMalloc || memoryFull) && free_Index < malloc_Index)
		{
			free(tempPointers[free_Index]); //free pointer at free_index
            free_Index++; //move onto the next index
            mallocsFreed++; //tells the while loop how many mallocs have been freed
		}
	}
	clock_t end = clock();//end clock counter
	double total_time = (double)(end - begin)/CLOCKS_PER_SEC;//calculate total execution time for testcase F
	printf("Test Case F ends-----------------------\n");
	return total_time;//return var to be used in main
}

/*
 * Function: randomNumber
 *-----------------------
 *   Simply creates a random from min to max (doesn't work well with 0 and 1 for min and max respectively)
 *
 *   Called by: test cases C-F
 *
 *   input: min (lowest number) and max (highest number they want)
 *
 *   returns: a random number from min to max
 */
int randomNumber(int min, int max)
{
    return (rand() % max) + min;
}
