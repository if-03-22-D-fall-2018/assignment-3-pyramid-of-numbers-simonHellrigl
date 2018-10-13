/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 3
 * Title:			Pyramid of Numbers
 * Author:    Simon Hellrigl
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/// The maximum number of digits allowed in a big int.
#define MAX_DIGITS 80

/** BigInt represents an integer number which can have MAX_DIGITS digits
*** @see MAX_DIGITS
*/
struct BigInt {
	int digits_count;

	/** array of digits of big int. */
	unsigned int the_int[MAX_DIGITS];
};

/** strtobig_int converts a string into a BigInt. If strtobig_int runs
*** against a character not between '0' and '9' the conversion stops
*** at this point.
*** @param *str The string to be converted.
*** @param len Number of characters in string to be converted.
*** @param *big_int The converted string now as BigInt.
* @return The number of characters converted.
*/
int strtobig_int(const char *str, int len, struct BigInt *big_int);



/** print_big_int() prints a BigInt.
*** @param *big_int The BigInt to be printed.
*/
void print_big_int(const struct BigInt *big_int);

/** multiply() multiplies a BigInt by an int.
*** @param big_int The BigInt to be multiplied.
*** @param factor The int value which is multiplied by BigInt.
*** @param *big_result The result of the multiplication.
*/
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result);

/** divide() multiplies a BigInt by an int.
*** @param big_int The BigInt to be divided.
*** @param divisor The int value by which we want to devide big_int.
*** @param *big_result The result of the division.
*/
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result);

/** copy_big_int() copies a BigInt to another BigInt.
*** @param from The source where we want to copy from.
*** @param *to The target where we want to copy to.
*/
void copy_big_int(const struct BigInt *from, struct BigInt *to);

/**
*** main() reads the base number from which the pyramid has to be calculated
*** into an array of char. The max. length of this number is MAX_DIGITS.
*** The number is checked to contain only digits. If not the program exits.
*** Then the inputted number is converted into a big int by calling the
*** function strtobig_int().
*** After the conversion the tower is calculated by calling the functions
*** multiply(), print_big_int(), and copy_big_int() consecutively from 2 to
*** 9 and then again with divide() instead of multiply() from 2 to 9.
***
*/
int main(int argc, char *argv[])
{
  char userinput[MAX_DIGITS];
	struct BigInt big_int;
	struct BigInt big_result;
	struct BigInt big_result_div;
	int factor=2;
	int divisor=9;
  int len;
	int convertedNumbers;


  printf("Pyramid of numbers\n");
  printf("Please enter a number: ");
  scanf("%s", userinput);
  len = strlen(userinput);
	convertedNumbers = strtobig_int(&userinput, len, &big_int);
	if (convertedNumbers == 0) {
		return 0;
	}

	for (size_t i = 0; i < 8; i++) {
		multiply(&big_int, factor, &big_result);
		give_numbers_correct_order(&big_result);
		give_numbers_correct_order(&big_int);
		print_big_int(&big_int);
		printf(" * %d = ",factor );
		print_big_int(&big_result);
		printf("\n");
		give_numbers_correct_order(&big_result);
		give_numbers_correct_order(&big_int);
		big_int = big_result;
		factor++;
	}
	give_numbers_correct_order(&big_result);
	for (size_t i = 0; i < 8; i++) {
		print_big_int(&big_result);
		divide(&big_result,divisor,&big_result_div);
		big_result = big_result_div;
		printf(" / %d = ",divisor);
		print_big_int(&big_result_div);
		printf("\n");
		divisor--;
	}





  return 0;
}

int strtobig_int(const char *str, int len, struct BigInt *big_int){

	int counter=0;
	for (int i = 0; i < len; i++) {

		if (str[i] >= '0' && str[i] <= '9') {
			(*big_int).the_int[counter] = str[len -i -1] -48;
			counter++;
		}

	}
big_int-> digits_count = counter;
return counter;
}


void print_big_int(const struct BigInt *big_int)
{
	bool isFirstDigit = true;
	for (int i = 0; i < big_int->digits_count; i++) {
		if (isFirstDigit && big_int->the_int[i] != 0)
		{
			isFirstDigit = false;
		}

		if (!isFirstDigit)
		{
			printf("%d", big_int->the_int[i]);
		}
	}
}


void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result)
{
	int overflow=0;
	int temp;
	big_result->digits_count = big_int->digits_count;
	for (int i = 0; i < big_int->digits_count; i++) {
		temp = big_int->the_int[i]*factor+overflow;
		overflow =0;
		if (temp>9) {

			if (i == big_int->digits_count-1) {
				big_result->digits_count++;
				big_result->the_int[i] = temp%10;
				big_result->the_int[i+1] = temp/10;
			}
			else{
				overflow = temp/10;
				big_result->the_int[i] = temp%10;
			}
		}
		else{
			big_result->the_int[i] = temp;
		}
	}

}

void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result)
{
	int overflow=0;
	int temp;

	for (size_t i = 0; i < big_int->digits_count; i++) {

		big_result->the_int[i] = 0;
		big_result->digits_count = i+1;
		temp = overflow*10 + big_int->the_int[i];
		if (divisor <= temp) {
			big_result->the_int[i] = temp / divisor;
			overflow = temp % divisor;
		}
		else{
			overflow = big_int->the_int[i];
		}
	}
}



//bringt die Ziffern in die richtige Reihenfolge
void give_numbers_correct_order(struct BigInt *big_int)
{
	int i = big_int->digits_count-1;
  int j = 0;
   while(i > j)
   {
     int temp = big_int->the_int[i];
		 int temp2 = big_int->the_int[j];
     big_int->the_int[i] = temp2;
     big_int->the_int[j] = temp;
     i--;
     j++;
   }
}
