/**********************************************************
*  addNumbers.c                                           *
*  ------------                                           *
*  A main source file for a program for HW #5.            *
*  Program sums a list of numbers it receives as input    *
*  arguments.                                             *
*  Uses functions from the numberString source module     *
*  and the virtualHeap module (for dynamic mem alloc)     *
**********************************************************/

/**********************************************************
*  DO NOT ADD ANY MORE INCLUDE DIRECTIVES TO THE PROGRAM  *
**********************************************************/
/*** standard libraries                                ***/
#include <stdio.h>
#include <string.h>
/*** shared header files contain function declarations ***/
#include "/share/ex_data/ex5/numberString.h"
#include "/share/ex_data/ex5/virtualHeap.h"


/**********************************************************
*  IF YOU ADD "HELPER FUNCTIONS", DECLARE THEM HERE AND   *
*  DEFINE THEM BELOW MAIN()                               *
**********************************************************/


/**********************************************************
* main function
* - read input arguments one by one as number strings
* - if argument is not valid number string, ignore it
* - standardize each input number string
* - sum the number strings and standardize the intermediate
*   result
* - print the sum and return the number of invalid input
*   arguments
* - uses dynamic memory allocation to store the intermediate
*   result. Reallocates exact space in each step
**********************************************************/
int main(int argc, char** argv) {

   int i, res, sumBufferLength, numInvalidArgs = 0;

   /*** free pointers to dynamically allocated arrays: ***/
   /*** - current sum                                  ***/
   /*** - updated sum (after summing one more number   ***/
   char *currentSum = NULL, *updatedSum = NULL;

   /*** constant number string representing 0          ***/
   char *zeroNumberString = "0";

   /*** initialize currentSum to point to a dynamic    ***/
   /*** allocated number string representing 0         ***/
   currentSum = ourMalloc(strlen(zeroNumberString+1));
   if(!currentSum) {
      printf("Out of memory\n");
      return -1;
   }
   strcpy(currentSum,zeroNumberString);

   /*** iterate through input arguments 1 .. argc      ***/
   for(i=1; i<argc; i++) {
//      printf("TEST: argv[%d]=%s ", i, argv[i]);
      /*** check validity of number string             ***/
      if(decimalPointPosition(argv[i]) < 0) {
         numInvalidArgs++;
//         printf(" is invalid number string\n");   // TEST
         continue;
      }

      /*** standardize number string                   ***/
      standardizeNumString(argv[i]);
//      printf(" after standardization = %s", argv[i]); // TEST

      /*** initial call to numSringSum to determine 
           the length required for buffer. Calling it
           with buffSize=0 guarantees that return
           value will be minus required buffer length  ***/
      sumBufferLength = -numStringSum(currentSum, argv[i], updatedSum, 0);
//      printf(" required buffer length for sum = %d, ", sumBufferLength); // TEST

      /*** allocate new buffer for sum                 ***/
      updatedSum = ourMalloc(sumBufferLength);
      if(!updatedSum) {
         printf("Out of memory\n");
         /*** free this also before returning ***/
         ourFree(currentSum);
         return -1;
      }

      /*** actual call to numSringSum                  ***/
      res = numStringSum(currentSum, argv[i], updatedSum, sumBufferLength);
      /*** check, just in case. We should never enter
           this condition                              ***/
      if(res != 1) {
         printf("Unexpected return value %d when summing argv[%d]=%s\n", res, i, argv[i]);
      }

//      printf(" sum is %s, ", updatedSum); // TEST
      /*** standardize sum                            ***/
      standardizeNumString(updatedSum);
//      printf(" standardized is %s\n", updatedSum); // TEST

      /*** free space used for previous sum and 
           update currentSum to point to udpatedSum   ***/
      ourFree(currentSum);
      currentSum = updatedSum;
      updatedSum = NULL;  // <-- this is just to maintain order
   } // end of for(i)

   /*** when loop is done, then there is a single 
        dynamically allocated block pointed to by
        currentSum, and it contians the sum of all 
        valid arguments. Note that updatedSum
        does not point to a block at this stage      ***/
   printf("The sum of the %d input numbers is %s\n", argc - 1 - numInvalidArgs, currentSum);
   ourFree(currentSum);

   /*** return number of invalid input arguments       ***/
   return numInvalidArgs;
}
