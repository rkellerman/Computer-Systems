/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
/*Using DeMorgans Law (xy)' = x' + y'*/
 
  return ~((~x)|(~y));
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
/* Get all ff's and turn off MSB */

  return ((~0)&(~(1<<31)));

}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
/* Retrieve lsb then create return value by adding to all FF's */
  
   int lsb = x & 0x01;
   return (!lsb + (~0));  
  
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
/* (x & -x) returns only LSB set in all cases */
  
   return (x & ((~x)+1));
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
/*Add bias if x < 0 and perform right shift */    
    
    int offset = (1<<n)+ (~0);
    int msb = (x>>31)&0x01;
    int result1 = (x>>n);
    int result2 = (x+offset)>>n;
    int checkmsb = msb + (~0);
    return ((checkmsb&result1)|(~checkmsb&result2)); 
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
/* Right shift and zero out 32-n bits on the left and account for special case of zero*/

  int checkn = !n + (~0);
  int result1 = (x>>n);
  int mask = (32 + (~n+1));
  int result2 =  result1 & (~((~0)<<mask));
  int finalresult = (checkn & result2)|(~checkn & result1);
  return finalresult;
}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
/* Return negation of sign of msb */
  
   return !((x>>31)&0x01);
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
/* Retrieve sign of both numbers - subtract if of same sign otherwise base decision on msb itself.Also consider both numbers being equal */

   int msbx = ((x>>31)&0x01);
   int msby = ((y>>31)&0x01); 
   int samesign = !(msbx^msby);
   int resultmask = !samesign + (~0);
   int result1 = !((x+(~y)+1)>>31)&0x01;
   int result2 = !msbx; 
   int result3 = !!(x^y);
   return ((resultmask&(result1&result3))|(~resultmask&result2));
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
/*Checkmsb and return x if x>=0 else 2's complement of x */

  int msb = (x>>31)&0x01;
  int checkmsb = msb + (~0);
  int result = (checkmsb & x)|(~checkmsb & ((~x)+1));
  return result;
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
/* All powers of 2 have only one set digit and negative numbers and zero aren't considered */
 int check1 = x&(x+(~0));
 int check2 = !x;
 int check3 = (x>>31)&0x01;
 return !(check1 + check2 + check3);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
/* Generate masks and use bit-shifting to count set 1's in groups of 1,2,4,8,16 */
 
 int result = 0;
 int smallmask1 = (0x55)|(0x55<<8);
 int mask1 = (smallmask1)|(smallmask1<<16);
 int smallmask2 = (0x33)|(0x33<<8);
 int mask2 = (smallmask2)|(smallmask2<<16);
 int smallmask3 = (0x0f)|(0x0f<<8);
 int mask3 = (smallmask3)|(smallmask3<<16);
 int mask4 = (0xff)|(0xff<<16);
 int mask5 = (0xff)|(0xff<<8);

 result = (x&mask1)+((x>>1)&mask1);
 result = (result&mask2)+((result>>2)&mask2);
 result = (result&mask3)+((result>>4)&mask3);
 result = (result&mask4)+((result>>8)&mask4);
 result = (result&mask5)+((result>>16)&mask5);

 return result; 
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
/*Invert msb of uf to change sign if negative and also check for NaN and zero as special cases*/
  
  int result=uf;
  int checksign = uf&0x80000000; 
  int exponent = (uf>>23)&0xff;
  int fraction = uf&0x7fffff;
  if(checksign&&uf)
    result = uf &(~(1<<31));
  if(exponent == 0xff && fraction)
    result = uf; 

    return result;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
/*   unsigned int result = 0;
   unsigned int arg;
   unsigned int quotient;
   int msb = (x>>31)&0x01;
   int power = 0;
   int radix =2;
   int bias = 127;
   int exponent = 0;
   unsigned int remainder=0;
   int bitposition = 0;
   int mask=0;

   arg = x;
   if(msb)
   arg = (~x) + 1;  
   
   quotient = arg;
   while(quotient>1)
   { remainder = arg;
     

//     printf("\nRemainder before%u",remainder); 
     remainder = remainder % radix;
//     printf("\nRemainder after %u",remainder); 

     if(arg)
{  //  {printf("\nArg %d Remainder %d Bitposition %d ",arg, remainder , bitposition); 
     mask |= (remainder<<(bitposition++));
     power ++;
      }
     quotient = arg / radix;
     arg = arg / radix ;
  //   printf("\nQuotient %u",quotient); 
   
    }
 //  printf("\nBitposition %d",bitposition); 
    if(bitposition>23)  *If you get more than 23 precision bits after normalization 
{
       mask = (mask >> (bitposition-23))&0x7fffff;
       bitposition = 23;
      } 

   if(x)
   exponent = power + bias;      
     
  // printf("\nPower %d",power); 

  // printf("\nBitposition %d",bitposition); 
   result |=  mask<<(23-bitposition);
   result |= (msb<<31);
   result |= (exponent<<23); 
   
   return result; */

   unsigned int result = 0;
   unsigned int arg;
   unsigned int quotient;
   int msb = x&0x80000000;
   int power = 0;
   int radix =2;
   int bias = 127;
   int exponent = 0;
   int bitposition = 0;
   int roundingbits = 0;
   int precisionbits = 0;
   int fraction = 0;
   unsigned int temp = 0;
   unsigned int precisionmask = 0xff;
   int maskshift = 0;
   arg = x;
   if(msb)
   arg = -x;  
   
   quotient = arg;
  
    while(quotient>1)
  {   
     quotient = quotient / radix;
     bitposition++;
   
    }
    power = bitposition;

//   printf("\nQuotient %u Bitposition %d Power %d",quotient,bitposition,power); 
  roundingbits = bitposition - 23;
  
 
  if(roundingbits>=0)
  {fraction = (arg >>roundingbits)&0x7fffff;
   maskshift = 8 - roundingbits;
   precisionbits = (arg&(precisionmask>>(maskshift)))<<(maskshift);
  } 
  else
  {
  maskshift = 32 - bitposition ;

//  printf("\nArg before modification %x",arg); 
  temp = (arg<<maskshift);
  temp = temp>>maskshift;
  fraction = temp; 
  fraction = fraction<<(23-bitposition);
//  printf("\nFraction in else %x",fraction); 
 }
 //  printf("\nFraction before modification %x",fraction); 
 //  printf("\nPower before modification %d",power); 
 
 /*  if(roundingbits>=0)
  {
 precisionbits = (arg&(precisionmask>>(maskshift)))<<(maskshift);

   } */

 
/*    if (roundingbits==1)
   precisionbits = (arg&0x01)<<7;

   if (roundingbits==2)
   precisionbits = (arg&0x03)<<6;
 
   if (roundingbits==3)
   precisionbits = (arg&0x07)<<5;
  
   if (roundingbits==4)
   precisionbits = (arg&0x0f)<<4;

   if (roundingbits==5)
   precisionbits = (arg&0x1f)<<3;

   if (roundingbits==6)
   precisionbits = (arg&0x3f)<<2;

   if (roundingbits==7)
   precisionbits = (arg&0x7f)<<1;

   if (roundingbits==8)
   precisionbits = (arg&0xff); */


/*   if (roundingbits>=3)
  {  printf("\nRounding bits %d",roundingbits); 
     printf("\nRounding Now %x",arg&0xff); 
   precisionbits = (arg>>(roundingbits-3))&0x07;
  } */
//    printf("\nPrecision bits %x",precisionbits); 
 
  if(precisionbits==0x80)
{
  

   if(fraction==0x7fffff)
   {  fraction = 0;
      power = power + 1;

    }

  else  if(fraction&0x01)
   fraction = fraction+1;  
} 

  if(precisionbits>(0x80))
{
  
//  printf("\nFraction before  modification in precision %x",fraction); 

   if(fraction==0x7fffff)
   {  fraction = 0;
      power = power + 1;

    }

   else
   fraction = fraction+1;  
  //  printf("\nFraction after modification in precision %x",fraction); 
}
    //  printf("\nFraction after modification %x",fraction); 
    //  printf("\nPower After modification %d",power); 

   if(arg)
   exponent = power + bias;      
  
   result  = msb;
   result |= (exponent<<23); 
   result |= fraction; 
   return result;


 }

