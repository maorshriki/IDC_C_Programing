#include <stdio.h>

/*************************************************
*  newFloat.c
*  ----------
*  A program containing functions for implementing
*  a new floating point type. Contains various auxiliary function
*************************************************/

/************************************************/
/* IMPORTANT NOTE:                              */
/* !! MODIFY CODE ONLY IN THE MARKED PLACES !!  */
/************************************************/


/********************************/
/**    SYMBOLIC CONSTANTS      **/
/********************************/
#define NUM_EXP_BITS 4
#define NUM_MAN_BITS (sizeof(int)*8 - NUM_EXP_BITS)

/********************************/
/**    FUNCTION DECLARATIONS   **/
/********************************/

/*********************************
* Problem 1.1
* computes the right-most bits
* of a given integer number
*********************************/
int rightBits(int n, int numBits);

/*********************************
* Problem 1.2
* computes the left-most bits
* of a given integer number
*********************************/
int leftBits(int n, int numBits);

/*********************************
* Problem 1.3
* computes the value (0 or 1) of
* a bit in a given integer number
*********************************/
int getBit(int n, int bitInd);


/*********************************
* Problem 2.1
* returns the exponent component
* of a new float
*********************************/
int getExponent(int newFloatNum);

/*********************************
* Problem 2.2
* returns the mantissa component
* of a new float
*********************************/
int getMantissa(int newFloatNum);

/*********************************
* Problem 2.3
* return the newFloat associated
* with the given exponent and
* mantissa.
*********************************/
int getNewFloat(int mantissa, int exponent);

/*********************************
* Problem 2.4
* return the newFloat associated
* with the sum of two newFloats
*********************************/
int newFloatSum(int newFloatNum1, int newFloat2);


/*********************************
* PRE-IMPLEMENTED
* return a dobule-type number equel in value to the number
* represented by a newFloat.
*********************************/
double newFloatToDouble(int newFloat);


/********************************/
/**    FUNCTION DEFINITIONS    **/
/********************************/

/*********************************
* Problem 1.1
* function rightBits
* params:
* n (int)
* numBits (int)
* return the numBits right bits of n
*********************************/
int rightBits(int n, int numBits) {
   /***      Problem 1.1 change here                   ***/
   /***      vvvvvvvvvvvvvvvvvvvvvvv                   ***/

   /*** end cases for numBits out of range             ***/
   if(numBits <= 0) return 0;
   if(numBits >= 8*sizeof(int)) return n;

   /*** (1<<numBits)-1 is a vector of numBit 1s       ***/
   return n & ((1<<numBits)-1);

   /***      ^^^^^^^^^^^^^^^^^^^^^^^                   ***/
   /***      Problem 1.1 change here                   ***/
}

/*********************************
* Problem 1.2
* function leftBits
* params:
* n (int)
* numBits (int)
* return the numBits left bits of n
*********************************/
int leftBits(int n, int numBits) {
   /***      Problem 1.2 change here                   ***/
   /***      vvvvvvvvvvvvvvvvvvvvvvv                   ***/

   /*** end cases for numBits out of range             ***/
   if(numBits <= 0) return 0;
   if(numBits >= 8*sizeof(int)) return n;

   /*** shift to the right as an unsigned to pad by 0s ***/
   return (unsigned int) n >> (8*sizeof(int)-numBits);

   /***      ^^^^^^^^^^^^^^^^^^^^^^^                   ***/
   /***      Problem 1.2 change here                   ***/
}

/*********************************
* Problem 1.3
* function getBit
* params:
* n (int)
* bitInd (int)
* return the bitInd'th bit of n (0 or 1)
*********************************/
int getBit(int n, int bitInd) {
   /***      Problem 1.3 change here                   ***/
   /***      vvvvvvvvvvvvvvvvvvvvvvv                   ***/

   /*** end cases for numBits out of range             ***/
   if(bitInd < 0 || bitInd >= 8*sizeof(int)) return 0;

   /*** shift to the right and take the parity bit     ***/
   return (n >> bitInd) & 1;

   /***      ^^^^^^^^^^^^^^^^^^^^^^^                   ***/
   /***      Problem 1.3 change here                   ***/
}

/*********************************
* Problem 2.1
* function getExponent
* params:
* newFloatnum (int)
* return the exponent associated with the newFloat
* newFloatNum. This is the non-negative integer associated
* with the left-most NUM_EXP_BITS bits in newFloatNum
*********************************/
int getExponent(int newFloatNum) {
   /***      Problem 2.1 change here                   ***/
   /***      vvvvvvvvvvvvvvvvvvvvvvv                   ***/

   /*** exponent is NUM_EXP_BITS left bits             ***/
   return leftBits(newFloatNum , NUM_EXP_BITS);

   /***      ^^^^^^^^^^^^^^^^^^^^^^^                   ***/
   /***      Problem 2.1 change here                   ***/
}

/*********************************
* Problem 2.2
* function getMantissa
* params:  
* newFloatnum (int)
* return the mantissa associated with the newFloat
* newFloatNum. This is the non-negative integer associated
* with all bits other than the right-most NUM_EXP_BITS bits
* in newFloatNum.
*********************************/
int getMantissa(int newFloatNum) {
   /***      Problem 2.2 change here                   ***/
   /***      vvvvvvvvvvvvvvvvvvvvvvv                   ***/

   /*** mantissa is NUM_MAN_BITS right bits             ***/
   return rightBits(newFloatNum, NUM_MAN_BITS);

   /***      ^^^^^^^^^^^^^^^^^^^^^^^                   ***/
   /***      Problem 2.2 change here                   ***/
}


/*********************************
* Problem 2.3
* function getNewFloat
* params:  
* mantissa (int)
* exponent (int)
* return the newFloat associated with the given exponent and mantissa
* Make the necessary adjustments to standardize the representation.
* If the value is out of bounds, then return the maximum new float
*********************************/
int getNewFloat(int mantissa, int exponent) {
   /***      Problem 2.3 change here                   ***/
   /***      vvvvvvvvvvvvvvvvvvvvvvv                   ***/

   /*** if mantissa takes up more than NUM_MAN_BITS bits
        then shift it to the right and adjust exponent  ***/
   while(leftBits(mantissa, NUM_EXP_BITS)) {
      mantissa = mantissa >> 1;
      exponent++;
   }

   /*** if mantissa takes up less than NUM_MAN_BITS bits
        and exponent is non-zero, then shift it to the left
        and adjust exponent                             ***/
   while((getBit(mantissa,NUM_MAN_BITS-1) == 0) && (exponent > 0)) {
      mantissa = mantissa << 1;
      exponent--;
   }

   /*** if exponent is out of bound, then return -1
        which represents the maximum new float         ***/
   if(leftBits(exponent,NUM_MAN_BITS))
      return -1;

   /*** input is valid, so we shift exponent to the left
        and add mantissa bits to the right
        (where they are)                               ***/
   return mantissa | (exponent << NUM_MAN_BITS);
                                               
   /***      ^^^^^^^^^^^^^^^^^^^^^^^                   ***/
   /***      Problem 2.3 change here                   ***/
}

/*********************************
* Problem 2.4
* function newFloatSum
* params:  
* newFloat1 (int)
* newFloat2 (int)
* return the newFloat associated with the sum of the two
* newFloats given as parameters. If one of the two input
* newFloats is invalid, or their sum is out of bounds,
* the function returns the maximum new float.
*********************************/
int newFloatSum(int newFloatNum1, int newFloatNum2) {
   /***      Problem 2.4 change here                   ***/
   /***      vvvvvvvvvvvvvvvvvvvvvvv                   ***/

   /*** get mantissa and exponent of input new floats ***/
   int exp1 = getExponent(newFloatNum1),
       exp2 = getExponent(newFloatNum2),
       man1 = getMantissa(newFloatNum1),
       man2 = getMantissa(newFloatNum2),
       expSum , manSum;


   /*** check validity of input parameters             ***/
   if((exp1>0) && getBit(man1,NUM_MAN_BITS-1)==0) 
      return -1; 
   if((exp2>0) && getBit(man2,NUM_MAN_BITS-1)==0)
      return -1;

   /*** set exp and man of sum according to max sum    ***/
   expSum = (exp1 >= exp2) ? exp1 : exp2;
   manSum = (exp1 >= exp2) ? (man1 + (man2>>(exp1-exp2))) : (man2 + (man1>>(exp2-exp1)));

   /*** check overflow of mantissa                     ***/
   if(getBit(manSum,NUM_MAN_BITS)==1) {
      manSum = manSum >> 1;
      expSum++;
   }

   /*** check overflow of exponent                     ***/
   if(getBit(expSum,NUM_EXP_BITS)==1)
      return -1;

   /*** manSum and expSum are valid, so we shift
        exponent to the left and add mantissa bits
        to the right (where they are)                  ***/
   return manSum | (expSum << NUM_MAN_BITS);

   /***      ^^^^^^^^^^^^^^^^^^^^^^^                   ***/
   /***      Problem 2.4 change here                   ***/
}

/*********************************
* PRE-IMPLEMENTED. DO NOT MODIFY THIS FUNCTIONS
* IMPLEMENTATION DEPENDS ON CORRECT
* IMPLEMENTATIONS OF getExponent and
* getMantissa (FROM PROBLEMS 2.1 AND 2.2)
*
* function newFloatToDouble
* params:  
* newFloatNum (int)
* return a dobule-type number equel in value to the number
* represented by a newFloat.
*********************************/
double newFloatToDouble(int newFloat) {

   int exponent = getExponent(newFloat),
       mantissa = getMantissa(newFloat);
   /*** check that the left-most bit in the mantissa
        is 1 when the exponent is > 0                  ***/
   if((exponent > 0) && (mantissa >> (NUM_MAN_BITS-1) == 0))
      return -1.0;

   /*** This loop computes 2^exponent efficiently
        by using at most 2 x log_2(exponent) multiplications
        After the i'th iteration of this while loop
        - temp holds 2^(2^i) (2.0 , 4.0 , 16.0 , 256.0 , ... )
        - num holds 2^x, where x is the integer represented
          by the right-most i bits of exponent
                                                       ***/
   double temp = 2.0, num = 1.0;
   while(exponent) {
      if(exponent & 1) num *= temp;
      temp *= temp;
      exponent = exponent >> 1;
   } // end of while(exponent)

   /*** return 2^exp x mantissa  ***/

   return num * mantissa;
  
}

