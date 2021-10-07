/**********************************************************
*  processExpenses.c                                      *
*  -----------------                                      *
*  A source file for a program that reads expense items   *
*  from a file and summarizes them in reports.            *
**********************************************************/
#include "/share/ex_data/ex6/expenseReport.h"
#include <stdio.h>
#include <string.h>


/*********************************************************/
/**                SYMBOLIC CONSTANTS                   **/
/*********************************************************/

/*** line length, including space for \n and \0        ***/
#define LINE_LEN 300

/*********************************************************/
/**               FUNCTION DECLARATIONS                 **/
/*********************************************************/

/**********************************************************
* Problem 2.1
* Function newExpenseItem
* -----------------------
* creates a new expense report object for a single expense
* based on information provided in a single string.
* params:
* - str  (char*)  - string containing information
*                          for expense item 
* Input string should have the following structure:
* "<SPACE1><TOKEN1><SPACE2><TOKEN2><SPACE3><TOKEN3>"
* The <SPACE> tokens correspond to sequences of space characters
* (<SPACE1> may be empty)
* <TOKEN1> should correspond to a valid date
* <TOKEN2> should correspond to a valid positive integer
* <TOKEN3> should contain a description of a single expense
*          item (no new line characters).
* Function creates a new ExpenseReport object based on
* this information and returns it.
* If string is incorrectly formatted or allocation failed,
* Function returns NULL.
**********************************************************/
ExpenseReport strToExpenseItem(const char* str);

/*********************************************************/
/**               FUNCTION DEFINITIONS                  **/
/*********************************************************/


/**********************************************************
* Problem 2.1
* Function newExpenseItem
* -----------------------
**********************************************************/
ExpenseReport strToExpenseItem(const char* str) {

   const char *ptr, *date, *description;
   double exp10=0.1, amount = 0.0;

   /*** skip spaces in <SPACE1> to reach <TOKEN1>      ***/
   for(ptr=str; *ptr == ' '; ptr++)
      ;

   /*** reached end of string --> <TOKEN1> is missing  ***/
   if(!*ptr)  return NULL;
   date = ptr;

   /*** skip non-spaces in <TOKEN1> to reach <SPACE2>  ***/
   for( ; *ptr && *ptr != ' '; ptr++)
      ;
   /*** skip spaces in <SPACE2> to reach <TOKEN2>      ***/
   for( ; *ptr == ' '; ptr++)
      ;

   /*** reached end of string --> <TOKEN2> is missing  ***/
   if(!*ptr)  return NULL;

   /*** convert TOKEN2 to double number value.
        Inspired by numStringToDouble from ex5.
        See /share/ex_sol/ex5/numberString.c
        for detailed explanation of the procedure.
   ***/
   /*** loop 1: left of decimal point - same as atoi() ***/
   for( ; *ptr>= '0' && *ptr <= '9' ; ptr++) 
      amount = 10 * amount + *ptr - '0';   

   /*** loop 2: right of decimal point - add digit
        value times appropriate exponent in 10         ***/
   if(*ptr == '.') {
      exp10=0.1;
      ptr++;
      for( ; *ptr>= '0' && *ptr <= '9' ; ptr++) { 
         amount += exp10 * (*ptr - '0');
         exp10 *= 0.1;
      }
   }   

   /*** character after amount number should be space  ***/
   if(*ptr != ' ')  return NULL;

   /*** skip spaces in <SPACE3> to reach <TOKEN3>      ***/
   for( ; *ptr == ' '; ptr++)
      ;
   /*** if <TOKEN3> is empty, return null              ***/
   description = ptr;
   if(!*description) return NULL;

   /*** create new expense item and return it          ***/
   return newExpenseItem(amount, date, description);
}
/*** end of strToExpenseItem ***/


/**********************************************************
* Problem 2.2
* main function
* -------------
**********************************************************/
int main( int argc, char** argv) {
   
   FILE* inFile = stdin;
   char  line[LINE_LEN+2];
   int numInvalidLines = 0, numBreakLines = 0;
   ExpenseReport expenseRep = NULL, lineItem;

   /*** set inFile only if first argument exists and is not - ***/
   if(argc>1 && (argv[1][0] != '-' || argv[1][1] != '\0')) {
      inFile = fopen(argv[1], "r");
      /*** check if file opened successfully                  ***/
      if(!inFile) {
         fprintf(stderr, "Cannot open %s for reading\n",argv[1]);
         return 1;
      }
   }

   /*** main loop for reading lines one by one                ***/
   while(fgets(line,LINE_LEN+2,inFile)) {
      /*** break line                                ***/
      if(line[0] == '#') {
         /*** print report, or message if report is empty     ***/
         if(expenseRep) {
            printExpenseReport(expenseRep);
            /*** no more use for old report, and set to NULL
                 to indicate that it is empty
            ***/
            freeExpenseReport(expenseRep);
            expenseRep = NULL;
         } else if(numBreakLines > 0) {
            printf("No expenses to report\n");
         }
         /*** print break line without first # character      ***/
         printf("%s",line+1);
         numBreakLines++;
         continue;
      } // end of if(line[0] == '#')

      /*** non-break line - should be an expense item         ***/
      /*** first, remove the '\n' in the end of the line      ***/
      line[strlen(line)-1] = '\0';
      /*** then, try to create an expense item                ***/
      lineItem = strToExpenseItem(line);

      /*** check if not valid expense item                    ***/
      if(!lineItem) {
         numInvalidLines++;
         continue;
      } 
      /*** if expense report is empty, this is first item     ***/
      if(!expenseRep) {
         expenseRep = lineItem;
         /*** this is not really needed, just in case         ***/
         lineItem = NULL;
         continue;
      } 

      /*** if expense item and report are valid, then
           merge them and free item
      ***/
      /*** merge and make sure allocation succeeded        ***/
      if(!mergeExpenseReports(expenseRep , lineItem)) {
         fprintf(stderr, "Out of memory\n");
         freeExpenseReport(lineItem);
         freeExpenseReport(expenseRep);
         if(inFile != stdin) fclose(inFile);
         return 2;
      }
      /*** free expense item, because it's no longer needed ***/
      freeExpenseReport(lineItem);
      /*** this is not really needed, just in case         ***/
      lineItem = NULL;
   } // end of while(fgets)

   /*** close file
        and print and free remaining expense report object    ***/
   if(inFile!= stdin)  fclose(inFile);

   if(expenseRep) {
      printExpenseReport(expenseRep);
      freeExpenseReport(expenseRep);
   } else if(numBreakLines > 0) {
      printf("No expenses to report\n");
   }

   if(numInvalidLines > 0) {
      if(inFile != stdin) {
         fprintf(stderr, "File %s contains %d invalid lines, which were ignored\n", argv[1], numInvalidLines);
      } else {
         fprintf(stderr, "File stdin contains %d invalid lines, which were ignored\n", numInvalidLines);
      }
      return 3;
   }


   return 0;
}
