/* 
 * CS:APP Data Lab 
 * 
 * <Name: Le'on Norfleet
    UID: 305771450>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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


NOTES:
  1. Our checker requires that you do NOT define a variable after 
     a statement that does not define a variable.

     For example, this is NOT allowed:

     int illegal_function_for_this_lab(int x, int y) {
      // this statement doesn't define a variable
      x = x + y + 1;
      
      // The checker for this lab does NOT allow the following statement,
      // because this variable definition comes after a statement 
      // that doesn't define a variable
      int z;

      return 0;
     }
     
  2. VERY IMPORTANT: Use the dlc (data lab checker) compiler (described in the handout)
     to check the legality of your solutions.
  3. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  4. Use the btest to check your functions for correctness.
  5. The maximum number of ops for each function is given in the
     header comment for each function. 

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest to verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  /*
  0x01 is 1, shifting 1 to the left 31 bits makes the new value 0x100...0
  flipping the bits of this makes 0x011...1 which is tmax
  */
  return ~(1 << 31);
}
/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
  /*
  the ! sign makes any value that is not 0, 0
  it also makes 0 into 1
  */
  return !x;
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /*
  i was able to understand how xor gates worked by looking
  at a simplified xor logic gate
  url for the image: shorturl.at/ackn8
  url for the image's site: shorturl.at/frz78
  */
  int gate1, gate2;

  gate1 = ~(~x & y);
  gate2 = ~(x & ~y);

  return ~(gate1&gate2);
}
/* 
 * isNotEqual - return 0 if x == y, and 1 otherwise 
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {
  /*
  xor returns 0 if both x and y have the same bits
  so adding a !! would make any non zero value become one
  the double !! negates itself in the case of 0
  */

  return !!(x ^ y);
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
  /*
  (x>>31) makes any negative number into -1(arithmetic shift)
  (x>>31) returns 0 for x >= 0
  !!x is to check whether or not x is positive or negative to mask the bits accordingly
  */
    return (x >> 31) | (!!x);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*
  if x is true do y, otherwise do z
  (!(x&~0) + ~0) - returns -1 if not 0, 0 otherwise
  (~(!(x&~0) + ~0)&z) - returns z if x is 0 and 0 if x is not 0
  if x is true then the second argument does nothing(it will be zero)
  if x is not true the first argument becomes zero and adds to the second argument
  which would become z
  */
  return ((!(x & ~0) + ~0) & y) + (~(!(x & ~0) + ~0) & z);
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  /*
  basic idea:
  turn the byte number in C that needs to be replaced into 1's
  Ex: 0x12345678 --> 0x12341178
  then shift n to be alligned correctly and replace 0's around it into 1's
  Ex: 0xbc --> 0xbc00 --> 0x1111bc11
  Finally & together the modified x and n values and return it
  */
  int newByte, mask, byteRemoved, inserter;

  newByte = (n<<3);
  mask = 0xff<<newByte;
  byteRemoved = ~(~x & ~(mask));
  inserter = (~(c << newByte) ^ (mask));

  return byteRemoved&inserter;
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /*
  Check that the second 4 bits is 3 using !((0x30>>4)^(x>>4))(will return 1 if 3, 0 otherwise)
  Check that the next 6 bytes(after the first 2) are/are not 0 using !((x&(~0<<8)&~0xff))
  which will return 0 if there is at least 1 non-zero bit in those 6 bytes, or 1 if there is not
  Check if the first 4 bits is no greater than 9 using !(((x&0x0f) + 6)>>4)
  this will cause the byte to extend only if the 4 bits were >= a
  */
  int arg1, arg2, arg3;

  arg1 = !((0x30>>4) ^ (x>>4));
  arg2 = !((x & (~0) & ~0xff));
  arg3 = !(((x & 0x0f) + 6) >> 4);

  return arg1&arg2&arg3;
}
/* 
 * subtractionOK - Determine if can compute x-y without overflow
 *   Example: subtractionOK(0x80000000,0x80000000) = 1,
 *            subtractionOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subtractionOK(int x, int y) {
  /*
  Inspiration from https://www.scaler.com/topics/c/overflow-and-underflow-in-c/
  
  !((x >> 31)^(y >> 31)) - returns 1 if x and y have the same sign(neg and neg or pos and pos)
  and 0 otherwise
  !(((x + (~y + 1)) >> 31) ^ (x >> 31)) - checks if the sign of the outcome of the subtraction
  is different than the sign of x
  if arg1 AND arg 2 returns 0, then overflow will happen
*/
  

  int arg1, arg2;

  arg1 = !((x >> 31)^(y >> 31));
  arg2 = !(((x + (~y + 1)) >> 31) ^ (x >> 31));

  return (arg1 | arg2);
}
// below are extra credits (4 pts in total)
// 2 points each (1 correctness pt + 1 performance pt)
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 */
int leastBitPos(int x) {
  /*
    x & ~x negate each other because ~x is the bit flipped version
    ~x + 1 is the two's comp version of x
    &'ing both together gives the mask that has a byte with the farthest right 1 in x
    */

  return x & (~x + 1);
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 */
int greatestBitPos(int x) {

  return x & (x + ~0);
}
