# Big Integer Arithmetic
This C library allows the users to perform arithmetic operations on very large integers(10000 digits),which otherwise, is available neither in C nor C++.

# *valid integers*
The arithmetic is allowed only for non-negative integers.

# Structure for the big integers
The integer is represented using a structure (INTAL-integer of arbritary length) that has an array of integers and its length.
The array is used to store the big integer, and its length is stored.

# Operations/Functions

intal_create(...)
takes a string(const char*) as parameter. And creates a big integer with that value, removing all the preceding zeros.
If invalid input is given, 'NULL' is returned by this function.

The below functions complete only if the integers are valid.

intal_compare(a,b)
Takes two generic pointers(void* a,void* b) as parameters, which represent valid big integers, then compares the two integers.
equivalent to :: return (a>b)?1:((a==b)?0:-1)
/*
  Other-wise
  if(a>b)return 1;
  else if(a==b)return 0;
  else return -1;
*/


intal_increment(a)
Takes a generic pointer(void*) as parameter that has to be incremented by 1.
equivalent to :: a+1

intal_decrement(a)
Takes a generic pointer(void*) as parameter that has to be decremented by 1, decrementing zero gives 0 (as we deal with only non-negative integers).
equivalent to :: a-1

intal_add(a, b)
Takes two generic pointers(void*) as parameters that have to be added.
equivalent to :: a+b

intal_diff(a, b)
Takes two generic pointers(void*) as parameters, for which the difference has to be calculated. It returns a non-negative integer.
equivalent to :: |a-b|

intal_multiply(a, b)
Takes two generic pointers(void*) as parameters, that are to be multiplied.
equivalent to :: a*b

intal_divide(a, b)
Takes two generic pointers(void*) as parameters (dividend,divisor), that are to be multiplied.
equivalent to :: a/b

intal_pow(a,b)
Takes two generic pointers(void*) as parameters (integer,power).
equivalent to :: a^b
