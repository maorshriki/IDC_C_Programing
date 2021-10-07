#include <string.h>
/*** shared header file contains all function declarations ***/
#include "/share/ex_data/ex5/numberString.h"
/**********************************************************
*  numberString.c                                         *
*  --------------                                         *
*  A code module containing functions for implementing    *
*  strings that represent numbers.                        *
**********************************************************/

/*********************************************************/
/*     IMPORTANT NOTE:                                   */
/*     !! MODIFY CODE ONLY IN THE MARKED PLACES !!       */
/*********************************************************/

/**********************************************************
* Problem 1.1
* function decimalPointPosition
* params:
* numStr  (const char*) - number string
* return the position of a decimal point withing a given
* number string.
* - If input is not a valid number string, return -1
* - If the input number string does not contain a decimal
*   point, return its length
**********************************************************/
int decimalPointPosition(const char* numStr) {
   /***      Problem 1.1 change here                   ***/
   /***      vvvvvvvvvvvvvvvvvvvvvvv                   ***/

   /*** decPos holds the return value
        pos    holds the current position              ***/
   int decPos=-1, pos;

   /*** scan the number string until reaching its end
        or until reaching an 'illegal' character       ***/
   for(pos=0; numStr[pos]; pos++) {
      /*** if reached dot, make sure it is the first
           dot and not the first char in string        ***/
      if(numStr[pos] == '.') {
         if(decPos > 0 || pos == 0)
            return -1;
         else
            decPos = pos;
      }
      /*** if reached a non-digit character that isn't
           a dot, this is not a valid number string    ***/
      else if(numStr[pos] < '0' || numStr[pos] > '9') {
         return -1;
      }
   } // end of for(pos)

   /*** if loop was completed, then either a single dot
        was found at decPos, or no dot was found (decPos==
        -1), and then we return the end position       ***/
   if(decPos < 0 && pos > 0)
      decPos = pos;
   return decPos;
   
   // return -123; <-- ORIGINAL LINE
   /***      ^^^^^^^^^^^^^^^^^^^^^^^                   ***/
   /***      Problem 1.1 change here                   ***/
}
/***      end of decimalPointPosition()                ***/

/**********************************************************
* Problem 1.2
* function numLeadingZeros
* params:
* numStr  (const char*) - number string
* return the number of leading zeros in a given number
* string.
* - If input is not a valid number string, return -1
**********************************************************/
int numLeadingZeros(const char* numStr) {
   /***      Problem 1.2 change here                   ***/
   /***      vvvvvvvvvvvvvvvvvvvvvvv                   ***/

   int pos, decPos = decimalPointPosition(numStr);
   if(decPos < 0) return -1;
 
   /*** scan number string from left to right until
        reaching a non-zero digit or one place
        left of decimal point                          ***/
   for(pos=0; pos<decPos-1 && numStr[pos] == '0'; pos++)
      ; // no statements in loop

   return pos;
      
   // return -123; <-- ORIGINAL LINE
   /***      ^^^^^^^^^^^^^^^^^^^^^^^                   ***/
   /***      Problem 1.2 change here                   ***/
}
/***      end of numLeadingZeros()                     ***/

/**********************************************************
* Problem 1.3
* function numTrailingZeros
* params:
* numStr  (const char*) - number string
* return the number of trailing zeros in a given number
* string.
* - If input is not a valid number string, return -1
**********************************************************/
int numTrailingZeros(const char* numStr) {
   /***      Problem 1.3 change here                   ***/
   /***      vvvvvvvvvvvvvvvvvvvvvvv                   ***/

   int pos, len, decPos = decimalPointPosition(numStr);
   if(decPos < 0) return -1;
   /*** if no decimal point, then no trailing 0s       ***/
   len = strlen(numStr);
   if(decPos >= len) return 0;

   /*** scan number string from right to left until
        reaching a non-zero character                  ***/
   for(pos=0; numStr[len-pos-1] == '0'; pos++) 
      ; // no statements in loop

   return pos;

   // return -123; <-- ORIGINAL LINE
   /***      ^^^^^^^^^^^^^^^^^^^^^^^                   ***/
   /***      Problem 1.3 change here                   ***/
}
/***      end of numTrailingZeros()                    ***/

/**********************************************************
* Problem 1.4
* function numStringIsInteger
* params:
* numStr  (const char*) - number string
* return 1 if a given num string represents an integer
* number and 0 otherwise.
**********************************************************/
int numStringIsInteger(const char* numStr) {

   int decPos = decimalPointPosition(numStr);

   /***      Problem 1.4 change here                   ***/
   /***      vvvvvvvvvvvvvvvvvvvvvvv                   ***/
   /*** IMPORTANT NOTE: JUST REPLACE THE RETURN
        VALUE WITH THE APPROPRIATE EXPRESSION!
        DO NOT ADD ANY OTHER STATEMENTS (LOOP OR
        CONDITIONS                                     ***/
   return decPos > 0 && decPos + 1 + numTrailingZeros(numStr) >= strlen(numStr);   // -123; <-- ORIGINAL RETURN VALUE
   /***      ^^^^^^^^^^^^^^^^^^^^^^^                   ***/
   /***      Problem 1.4 change here                   ***/
}
/***      end of numStringIsInteger()                  ***/

/**********************************************************
* Problem 1.5
* function numStringToDouble
* params:
* numStr  (const char*) - number string
* return the double-percision value corresponding to a
* given number string.
* - If input is not a valid number string, return -1.0
**********************************************************/
double numStringToDouble(const char* numStr) {
   /***      Problem 1.5 change here                   ***/
   /***      vvvvvvvvvvvvvvvvvvvvvvv                   ***/

   int pos, decPos = decimalPointPosition(numStr);
   double exp10, value = 0.0;
   if(decPos < 0) return -1.0;

   /*** throughout the two loops in this function,
        variable value holds the value of the number
        string which is the prefix of numStr ending
        in position 0 [ initialize with value = 0.0 ]  ***/

   /*** loop 1: left of decimal point - same as atoi() ***/
   for(pos=0; pos<decPos ; pos++) 
      value = 10 * value + numStr[pos] - '0';   

   /*** loop 2: right of decimal point - add digit value
        times appropriate exponent in 10               ***/
   exp10=0.1;
   for(pos=decPos+1; numStr[pos] ; pos++) { 
      value += exp10 * (numStr[pos] - '0');
      exp10 *= 0.1;
   }   

   return value;
   
   // return -123.0; <-- ORIGINAL LINE
   /***      ^^^^^^^^^^^^^^^^^^^^^^^                   ***/
   /***      Problem 1.5 change here                   ***/
}
/***      end of numStringToDouble()                   ***/

/**********************************************************
* Problem 1.6
* function standardizeNumString
* params:
* numStr  (char*) - number string
* converts given number string to standard form by removing
* all leading and trailing zeros.
* writes over the given num string.
* return 1 if already standard and 0 otherwise
* - If input is not a valid number string, then does
*   nothing and returns 0.
**********************************************************/
int standardizeNumString(char* numStr) {
   /***      Problem 1.6 change here                   ***/
   /***      vvvvvvvvvvvvvvvvvvvvvvv                   ***/

   int res = 1, pos, lastDigit, shiftOffset = numLeadingZeros(numStr);
   /*** check for validity of input                    ***/
   if(shiftOffset < 0) return 0;

   /*** shiftOffset holds the number of characters we
        have to "shift left" due to leading zeros.
        lastDigit holds the position of the last digit
        that is not a trailing zero                   ***/
   lastDigit = strlen(numStr) - numTrailingZeros(numStr) - 1;

   /*** set res=1 if there are leading or trailing 0s ***/
   res = (shiftOffset + numTrailingZeros(numStr) == 0);

   /*** shifting loop - enter only if offset > 0      ***/
   if(shiftOffset == 0) {
      pos=lastDigit+1;
   } else {
      for(pos=0; pos+shiftOffset <= lastDigit; pos++ ) {
        numStr[pos] = numStr[pos+shiftOffset];
      }
   }

   /*** if last character is the decimal digit,
        then remove it and mark as non-standard       ***/
   if(numStr[pos-1]=='.') {
      pos--;
      res = 0;
   }
   
   /*** add terminating '\0'                          ***/
   numStr[pos] = '\0';
   return res;

   // return -123.0; <-- ORIGINAL LINE
   /***      ^^^^^^^^^^^^^^^^^^^^^^^                   ***/
   /***      Problem 1.6 change here                   ***/
}
/***      end of standardizeNumString()                ***/

/**********************************************************
* Problem 1.7
* function numStringSum
* params:
* numStr1    (const char*) - number string
* numStr2    (const char*) - number string
* numStrSum  (char*)       - buffer used for writing the result
* buffSize   (int)         - maximum number of character 
*                            (including '\0') that function
*                            is allowed to write to buffer
* writes the number string corresponding to the sum of two
* given number strings into a specified buffer.
* If one of the two number strings is invalid, or space is 
* insufficient to write the sum, then does not write anything
* and returns 0. Otherwise, writes sum and returns 1.
* Does not standardize the output.
**********************************************************/
int numStringSum(const char* numStr1, const char* numStr2, char* numStrSum, int buffSize) {
   /***      Problem 1.7 change here                   ***/
   /***      vvvvvvvvvvvvvvvvvvvvvvv                   ***/

   int leftOverhangLen, overlapLen, rightOverhangLen,
       sumLen, posSource, posTarget, carry,
       decPos1 = decimalPointPosition(numStr1),
       decPos2 = decimalPointPosition(numStr2);

   /*** pointers to the start of:
        - left and right overhangs
        - overlap in numStr1 and numStr2               ***/
   const char *leftOverhang, *rightOverhang, *overlap1, *overlap2;

   /*** if one of the number strings is invalid
        do nothing and return 0                        ***/
   if(decPos1 < 0 || decPos2 < 0) return 0;

   /*** determine left overhang and start of overlap   ***/
   overlap1 = numStr1;
   overlap2 = numStr2;
   if(decPos1 < decPos2) {
      leftOverhang = numStr2;
      leftOverhangLen = decPos2 - decPos1;
      overlap2 += leftOverhangLen;
   } else {
      leftOverhang = numStr1;
      leftOverhangLen = decPos1 - decPos2;
      overlap1 += leftOverhangLen;
   }

   /*** determine length of overlap and right overhang ***/
   rightOverhangLen = strlen(overlap1) - strlen(overlap2);
   if(rightOverhangLen < 0) {
      rightOverhangLen = -rightOverhangLen;
      overlapLen       = strlen(overlap1);
      rightOverhang    = overlap2 + overlapLen;
   } else {
      overlapLen       = strlen(overlap2);
      rightOverhang    = overlap1 + overlapLen;
   }

   /*** determine the length of the sum + terminatiion ***/
   sumLen = leftOverhangLen + rightOverhangLen + overlapLen + 1;
   /*** add 1 if there is risk of overflow, which is
        when the left digit in left overhang is 9 or
        if left overhang is empty and the sum of two 
        left digits in overlap is >= 9                 ***/
   if( (leftOverhangLen  > 0 && *leftOverhang == '9') ||
       (leftOverhangLen == 0 && (*overlap1 + *overlap2 >= '0' + '9')) )
      sumLen++;

   /*** if buffSize is not enough, abort               ***/
   if(buffSize < sumLen) return -sumLen;

   /*** loop 1: copy right overhang to sum, including
        terminating '\0'                               ***/
   for(posSource = rightOverhangLen, posTarget = sumLen-1;
       posSource >= 0;
       posSource--, posTarget--) 
   {
      numStrSum[posTarget] = rightOverhang[posSource];
   }// end of loop 1

   /*** loop 2: sum overlap, and maintain carry from
        one digit to the next                          ***/
   carry = 0;
   for(posSource = overlapLen-1;
       posSource >= 0;
       posSource--, posTarget--) 
   {
      /*** if encountered decmal dot, then copy        ***/
      if(overlap1[posSource] == '.') {
         numStrSum[posTarget] = '.';
      }
      /*** compute digit sum + carry from prev digit   ***/
      else {
         numStrSum[posTarget] = overlap1[posSource] + overlap2[posSource] - '0' + carry;
         if(numStrSum[posTarget] > '9') {
            numStrSum[posTarget] -= 10;
            carry = 1;
         } else {
            carry = 0;
         }
      }
   }// end of loop 2

   /*** loop 3: left overhang, no summing, but
        propagate carry                                ***/
   for(posSource = leftOverhangLen-1;
       posSource >= 0;
       posSource--, posTarget--)
   {
      numStrSum[posTarget] = leftOverhang[posSource] + carry;
      if(numStrSum[posTarget] > '9') {
         numStrSum[posTarget] -= 10;
         carry = 1;
      } else {
         carry = 0;
      }
   }// end of loop 3

   /*** check overflow                                 ***/
   if(posTarget==0) {
      numStrSum[0] = '0' + carry;
   } else if(posTarget > 0) {
      return -3;   // should not reach here - overshot the length of sum
   } else if(carry > 0) {
      return -30;  // should not reach here - overflow without having space
   }

   return 1;

   // return -123; <-- ORIGINAL LINE
   /***      ^^^^^^^^^^^^^^^^^^^^^^^                   ***/
   /***      Problem 1.7 change here                   ***/
}
/***      end of numStringSum()                   ***/

