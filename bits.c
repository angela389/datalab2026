/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~ (~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    int sx = x >> 31;
    int sy = y >> 31;
    int zx = !x;
    int zy = !y;

    if (zx && zy)
        return 1;
    if (zx && !zy)
        return 0;
    if (!zx && zy)
        return 0;

    return !(sx ^ sy);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r = 0;
    int s;

    s = (v > 0xFFFF) << 4;
    r = r | s;
    v = v >> s;

    s = (v > 0xFF) << 3;
    r = r | s;
    v = v >> s;

    s = (v > 0xF) << 2;
    r = r | s;
    v = v >> s;

    s = (v > 0x3) << 1;
    r = r | s;
    v = v >> s;

    r = r | (v > 1);

    return r;

}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int n_shift = n << 3;
    int m_shift = m << 3;

    int n_byte = (x >> n_shift) & 0xff;
    int m_byte = (x >> m_shift) & 0xff;

    int mask = (0xff << n_shift) | (0xff << m_shift);

    x = x & ~mask;

    return x | (n_byte << m_shift) | (m_byte << n_shift);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned mask1 = 0x55555555;
    unsigned mask2 = 0x33333333;
    unsigned mask4 = 0x0f0f0f0f;
    unsigned mask8 = 0x00ff00ff;

    v = ((v >> 1) & mask1) | ((v & mask1) << 1);

    v = ((v >> 2) & mask2) | ((v & mask2) << 2);

    v = ((v >> 4) & mask4) | ((v & mask4) << 4);

    v = ((v >> 8) & mask8) | ((v & mask8) << 8);

    v = (v >> 16) | (v << 16);

    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask = ~(((1 << 31) >> n) << 1);
    return (x >> n) & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
int n = 0;
    int all = !(~x);
    int s;

    s = !(~(x >> 16)) << 4;
    n = n | s;
    x = x << s;

    s = !(~(x >> 24)) << 3;
    n = n | s;
    x = x << s;

    s = !(~(x >> 28)) << 2;
    n = n | s;
    x = x << s;

    s = !(~(x >> 30)) << 1;
    n = n | s;
    x = x << s;

    s = !(~(x >> 31));
    n = n | s;

    return n + all;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) 
{
    unsigned sign, abs, frac; 
    int e, shift; 
    unsigned round; 

    if (x == 0) 
        return 0; 

    sign = x & 0x80000000; 

    abs = x; 
    if (sign) 
        abs = -x; 

    e = 31; 
    while (!(abs >> e)) 
        e--; 

    shift = e - 23;

    if (shift > 0) { 
        frac = abs >> shift;

        round = abs << (32 - shift);

        if ((round > 0x80000000) |
            ((round == 0x80000000) & (frac & 1)))
            frac++;

        if (frac >> 24) { 
            e++; 
            frac >>= 1; 
        } 
    } 
    else { 
        frac = abs << (-shift); 
    } 

    return sign | 
        ((e + 127) << 23) | 
        (frac & 0x7fffff);
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign;
    unsigned exp;
    unsigned frac;

    sign = uf & 0x80000000;
    exp = (uf >> 23) & 0xff;
    frac = uf & 0x7fffff;

    if (exp == 0xff)
        return uf;

    if (exp == 0) {
        frac = frac << 1;
        return sign | frac;
    }

    exp = exp + 1;

    if (exp == 0xff)
        frac = 0;

    return sign | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int sign;
    int exp;
    int E;
    unsigned frac_hi;
    unsigned frac_lo;
    unsigned val;

    sign = uf2 >> 31;

    exp = (uf2 >> 20) & 0x7ff;

    /* exp == 0x7ff (NaN or Infinity) */
    if (!(exp + ~0x7ff + 1))
        return 0x80000000;

    E = exp + ~1022;

    /* E < 0 */
    if (E < 0)
        return 0;

    /* E > 30 */
    if (E > 30)
        return 0x80000000;

    /*
     * frac_hi:
     * hidden bit + high 20 bits of fraction
     *
     * actual value:
     * (1.frac) * 2^E
     */
    frac_hi = (uf2 & 0xfffff) | 0x100000;
    frac_lo = uf1;

    if (E > 19) {
        val = (frac_hi << (E - 20)) |
              (frac_lo >> (52 - E));
    } else {
        val = frac_hi >> (20 - E);
    }

    if (sign)
        return -val;

    return val;
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
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    unsigned exp;
    unsigned frac;

    if (x > 127)
        return 0x7f800000;

    if (x < -149)
        return 0;

    if (x >= -126) {
        exp = x + 127;
        return exp << 23;
    }

    frac = 1 << (x + 149);

    return frac;
}
