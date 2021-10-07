/**********************************************************
*  expenseReport.c                                        *
*  ---------------                                        *
*  A source file for code module containing functions     *
*  for implementing and ExpenseReport object.             *
**********************************************************/
#include "/share/ex_data/ex6/expenseReport.h"
#include "/share/ex_data/ex6/virtualHeap.h"
#include <stdio.h>
#include <string.h>


/*********************************************************/
/**                SYMBOLIC CONSTANTS                   **/
/*********************************************************/
#define DATE_LEN 8

/*********************************************************/
/**                   TYPE DEFINITIONS                  **/
/*********************************************************/

/**********************************************************
* Problem 1.1
* Strcuture type for object ExpenseReport
******************************************/
struct ExpenseReport {
   /*** total amount of all expenses in US Dollars ***/
   double totalAmount;
   /*** start and end date of period for expenses
        Format: YYYYMMDD
   ***/
   char startDate[DATE_LEN];
   char   endDate[DATE_LEN];
   /*** description if all items corresponding to
        the reported expenses. Description of each
        item is given in free text, and different
        items are separated using '\n'
   ***/
   char* description;
};


/*********************************************************/
/**               FUNCTION DEFINITIONS                  **/
/*********************************************************/


/**********************************************************
* Problem 1.2
* Function newExpenseItem
* -----------------------
* creates a new expense report object for a single expense
* params:
* - amount      (double) - amount in $s associated with expense
* - date        (char*)  - pointer to an 8-char array holding date
*                          in format YYYYMMDD
* - description (char*)  - a string containing a description of the expense
*                          the string should not contain newlines ('\n')
*                          to indicate that this is a single expense
* Parameters should satisfy the following:
* - expense should be non-negative
* - year  in date should be in range 1950 - 2020
* - month in date should be in 01 - 12
* - day   in date should be in 01 - 31
*         (function does not check for actual match of day and month)
* - description should not contain a newline char ('\n')
* If input is invalid, function returns NULL
* Otherwise, the function allocates space for the struct and description
* on the heap, sets all members according to parameter values, 
* and returns a pointer to the allocated structure.
* If allocation fails, function returns NULL
**********************************************************/
ExpenseReport newExpenseItem(double amount, const char* date, const char* description) {
   ExpenseReport expenseRep = NULL;
   int i, year, month, day;

   /*** check input: date and description             ***/
   if(amount <= 0 || strchr(description, '\n'))
      return NULL;

   /*** check input: date consists of digits          ***/
   for(i=0; i<DATE_LEN; i++) {
      if(date[i] < '0' || date[i] > '9') {
         return NULL;
      }
   }

   /*** check input: date ranges                      ***/
   year  = (date[0]-'0')*1000 + (date[1]-'0')*100 + (date[2]-'0')*10 + (date[3]-'0');
   month = (date[4]-'0')*10   + (date[5]-'0');
   day   = (date[6]-'0')*10   + (date[7]-'0');

   if(year < 1950 || year > 2020 || month < 1 || month > 12 || day < 1 || day > 31)
      return NULL;

   /*** at this stage, we know that the input is
        correctly formatted, and we can allocate
        space for the object
   ***/
   expenseRep = ourMalloc(sizeof(struct ExpenseReport));
   if(!expenseRep)
      return NULL;

   /*** allocate separate space for string, including
        an extra character for the terminating '\0'
   ***/
   expenseRep->description = ourMalloc(1+ strlen(description));
   if(!expenseRep->description) {
      ourFree(expenseRep);
      return NULL;
   }

   /*** set all structure fields                      ***/
   expenseRep->totalAmount = amount;
   strncpy(expenseRep->startDate   , date , DATE_LEN);
   strncpy(expenseRep->endDate     , date , DATE_LEN);
   strcpy (expenseRep->description , description    );

   return expenseRep;
}
/*** end of function newExpenseItem ***/


/**********************************************************
* Problem 1.3
* Function freeExpenseReport
* --------------------------
* frees all space allocated by an expense report
* params:
* - expenseRep  (ExpenseReport) - pointer to expense report object
* Frees all allocated space (structure and description)
**********************************************************/
void freeExpenseReport(ExpenseReport expenseRep) {
   /*** First free the description string, which
        is allocated outside of the structure,
        and then free the structure
   ***/
   ourFree(expenseRep->description);
   ourFree(expenseRep);
   return;
}
/*** end of function freeExpenseReport ***/

/**********************************************************
* Problem 1.4
* Function mergeExpenseReports
* ----------------------------
* merges one expense report into the other
* params:
* - expenseRep1  (ExpenseReport) - pointer to expense report object
* - expenseRep2  (ExpenseReport) - pointer to expense report object
* Merges expenseRep2 into expenseRep1.
* The function modifies expenseRep1 to include all the expenses
* originally listed in it as well as the expenses listed in
* expenseRep2. The new total amount should be the sum of the
* total amounts of the two reports, the new date range should
* be the minimal range that covers both ranges, and the new
* description should consist of all items in expenseRep1
* followed by the items of expenseRep2 (separated by a newline).
* To obtain this, we need to reallocate space for the description
* string!!
* The contents of expenseRep2 should remain unchanged.
* The function returns a pointer to the modified object expenseRep1.
**********************************************************/
ExpenseReport mergeExpenseReports(ExpenseReport expenseRep1, ExpenseReport expenseRep2) {

   /*** start by allocating space for the merged descrption 
        string, because if this fails, we return NULL.
        Length of merged description is sum of lengths + 2
        (to hold the separating '\n' and the terminating '\0'.
   ***/
   int mergedDescLen = 2 + strlen(expenseRep1->description) + strlen(expenseRep2->description);
   char* mergedDescription = ourMalloc(mergedDescLen);
   if(!mergedDescription)
      return NULL;

   /*** generate merged description                   ***/
   strcpy(mergedDescription , expenseRep1->description);
   strcat(mergedDescription , "\n");
   strcat(mergedDescription , expenseRep2->description);


   
   /*** free old description and update pointer to new
        merged string
   ***/
   ourFree(expenseRep1->description);
   expenseRep1->description = mergedDescription;

   /*** update the total amount                       ***/
   expenseRep1->totalAmount += expenseRep2->totalAmount;

   /*** update the start date of expenseRep1 iff
        expenseRep2 has an earlier start date
   ***/
   if(strncmp(expenseRep1->startDate , expenseRep2->startDate, DATE_LEN) > 0)
      strncpy(expenseRep1->startDate , expenseRep2->startDate, DATE_LEN);

   /*** update the end date of expenseRep1 iff
        expenseRep2 has a later end date
   ***/
   if(strncmp(expenseRep1->endDate   , expenseRep2->endDate  , DATE_LEN) < 0)
      strncpy(expenseRep1->endDate   , expenseRep2->endDate  , DATE_LEN);


   return expenseRep1;
}
/*** end of function mergeExpenseReports ***/

/**********************************************************
* Problem 1.5
* Function numExpenseItems
* ------------------------
* returns the number of expense items in a given report
* params:
* - expenseRep  (ExpenseReport) - pointer to expense report object
* Returns the number of expense items in a given report
* Number of items is defined by the number of newlines in the
* description string + 1.
**********************************************************/
int numExpenseItems(ExpenseReport expenseRep) {

   /*** initialize number of items at 1                ***/
   int numItems = 1;
   /*** point to the first newline in description, if exists
   ***/
   char* ptr = strchr(expenseRep->description,'\n');

   while(ptr) {
      numItems++;
      /*** point to the next newline
           (first newline in string starting from ptr+1)
      ***/
      ptr = strchr(ptr+1,'\n');
   }

   return numItems;
}
/*** end of function numExpenseItems ***/

/**********************************************************
* Problem 1.6
* Function printExpenseReport
* ---------------------------
* prints an expense report
* params:
* - expenseRep  (ExpenseReport) - pointer to expense report object
* Prints expense report in the following format:
*
* <N> expense(s) reported between DD/MM/YYYY and DD/MM/YYYY:
* < ITEM 1 >
* < ITEM 2 >
* . . .
* < ITEM N >
* Total amount: <TOTAL_AMOUNT> NIS
*
* Where <N> is printed in a field width of 4, and
* <TOTAL_ AMOUNT> is printed in precision of up to
* one position after the decimal point (10 AGOROT resolution).
**********************************************************/
void printExpenseReport(ExpenseReport expenseRep) {
   char *startDate = expenseRep->startDate,
        *endDate = expenseRep->endDate;

   /*** print header line with number of items and formatted dates ***/
   printf("%3d expense(s) reported between %c%c/%c%c/%c%c%c%c and %c%c/%c%c/%c%c%c%c:\n",
          numExpenseItems(expenseRep),
          startDate[6], startDate[7],startDate[4],startDate[5],startDate[0],startDate[1],startDate[2],startDate[3],
            endDate[6],   endDate[7],  endDate[4],  endDate[5],  endDate[0],  endDate[1],  endDate[2],  endDate[3]  );

   /*** print list of items + new line at the end ***/
   printf("%s\n", expenseRep->description);

   /*** print total amount                        ***/
   printf("Total amount: %.1lf NIS\n", expenseRep->totalAmount);

   return;
}
/*** end of function printExpenseReport ***/

