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

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
	return ~(~(x & (~y)) & ~((~x) & y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {

  return 1<<31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // consider the uniquness of Tmax: 0111...1   only Tmax + 1 == Tmin
  // besides we have Tmax == ~Tmin
	int i = x + 1;
	x = x +i;
	x = ~x;
	i = !i;
	x += i;
	return !x;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int all_odd_mask = 0xAA + (0xAA << 8);
	all_odd_mask = all_odd_mask + (all_odd_mask << 16);
  x = x & all_odd_mask;
	x = x ^ all_odd_mask;
	return !x;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	x = ~x;
 	x += 1;	
	return x;
}
//3
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
  int mask = 0xFF, part_1, part_2, tp_1, tp_2;
	mask = ~0;
	mask = mask ^ 0xF;
	// **** 0000
	part_1 = (x & mask) ^ 0x30;
	part_1 = !part_1;
	// 0000 ****
	tp_1 = !!(0x8 & x); 
	tp_2 = !!(0x6 & x);
	part_2 = !(tp_1 & tp_2);
	return part_1 & part_2;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int tmp;
	x = !(!x);
	x = ~x + 1;     // change 0 -> 0000..0   1-> 1111..1
	tmp = x & y;
	x = z & (~x);
	return x | tmp;     // consider return a shape like (x & y) | (!x & z)
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // consider that we check the MSB of (y - x) if (y - x) >= 0 return 1 
  // may overflow when one is pos and one is neg
  // compare their MSB at first
  int ms_x, ms_y, ms_v;
  int msb = 1 << 31;
  ms_x = x & msb; ms_y = y & msb;
  ms_v = ms_x ^ ms_y;
  ms_x = !!ms_x;
  ms_v = !!ms_v;
  // MSB same, using their differential
  x = (~x) + 1; // -x 
  y = y + x;
  y = y & msb;
  y = !y;
	return  (ms_v & ms_x) | ((!ms_v) & y);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // consider that only arithmaticNeg(0) == 0 using lowbit to make all bits above lowbit 1s
  x = x | (~x + 1);
  x = x >> 31;
  return x + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int sign = x >> 31;
  x = (sign & (~x)) | ((~sign) & x);
  int b16, b8, b4, b2, b1;

  // upper 16bit
  b16 = !!(x >> 16) << 4;
  x = x>> b16;
  b8 = !!(x >> 8) << 3;
  x = x>> b8;
  b4 = !!(x >> 4) << 2;
  x = x>> b4;
  b2 = !!(x >> 2) << 1;
  x = x>> b2;
  b1 = !!(x >> 1);
  x = x>> b1;
  return b16+b8+b4+b2+b1+x+1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  int exp = (uf&0x7f800000)>>23;
  int sign = uf&(1<<31);
  if(exp==0) return uf<<1|sign;
  if(exp==255) return uf;
  exp++;
  if(exp==255) return 0x7f800000|sign;
  return (exp<<23)|(uf&0x807fffff);
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int sign = uf & (1 << 31);
  int exp = (uf & 0x7f800000)>>23;
  int sif = uf & 0x007fffff;
  // printf("sign is %x\n", sign);
  // printf("exp is %x\n", exp);
  // printf("sif is %x\n", sif);
  exp -= 127;
  if (exp > 30) return 0x80000000;
  if (exp < 0) return 0;
  sif = sif | 0x00800000;
  int valid_bit = exp + 1;
  int ans;  
 
  if (valid_bit < 24) {
    int mask = ((1 << valid_bit) - 1) << (24 - valid_bit);
    ans = (mask & sif) >> (24 - valid_bit);
  } else {
    ans = sif << (valid_bit - 24);
  }
  if (sign)   // if it's negtive, using two's complement
    ans = ~ans + 1;
  return ans;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  unsigned INF = 0x7f800000;
  if (x > 127)
    return INF;
  if (x < -150 )   // mini denorm would be [ 0  0000..0 0000...01] 24 + 126
    return 0;      //                     |sig| |exp|  |frac|

  x += 127;
  unsigned ans = 0;
  ans = ans | (x << 23);
  if (x < 0) {
    ans = ans | (1 << (23 + x));
  }
  return ans;
}
