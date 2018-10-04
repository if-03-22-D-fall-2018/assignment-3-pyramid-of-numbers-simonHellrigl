#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct BigInt{
  int digits[160];
  int digitCount =0;
};


int main(int argc, char const *argv[]) {
  const int MAX_DIGITS=160;
  char userinput[MAX_DIGITS];
  int lenght;

  printf("Pyramid of numbers");
  printf("Please enter a number: ");
  scanf("%s", &userinput);
  lenght = strlen(userinput);
  printf("%d\n", lenght);

  return 0;
}
