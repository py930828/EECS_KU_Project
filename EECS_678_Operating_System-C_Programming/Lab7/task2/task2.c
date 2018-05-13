#include <stdio.h>
#include <stdlib.h>

/* IMPLEMENT ME: Declare your functions here */
typedef int ( *function_pointer )(int a, int b);
int add (int a, int b);
int subtract( int a, int b);
int multiply( int a, int b);
int divide( int a, int b);
int main (void)
{
	/* IMPLEMENT ME: Insert your algorithm here */
	function_pointer pointer[4];
	pointer[0] = add;
	pointer[1] = subtract;
	pointer[2] = multiply;
	pointer[3] = divide;
	printf(" Operand 'a' : ");
	int a = 0;
	int b = 0;
	int num = 0;
	scanf( "%d", &a);
	printf(" | Operand 'b' : ");
	scanf( "%d", &b);
	printf("\n Specify the operation to perform (0 : add | 1 : subtract | 2 : Multiply | 3 : divide): ");
	scanf( "%d", &num );
	printf( "%d \n", pointer[num](a, b) );

	return 0;
}

/* IMPLEMENT ME: Define your functions here */
int add (int a, int b) { printf ("Adding 'a' and 'b'\n"); return a + b; }
int subtract (int a, int b) { printf ("subtract 'a' and 'b'\n"); return a - b; }
int multiply (int a, int b) { printf ("multiply 'a' and 'b'\n"); return a * b; }
int divide (int a, int b) { printf ("divide 'a' and 'b'\n"); return a / b; }
