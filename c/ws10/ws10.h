#include <stddef.h>


char *Itoa(int value, char *string, int base);
int Atoi(char* str);
void IsLittleEndian();
void SelectedElements(char a1[], int size1, char a2[], int size2, char a3[], int size3);

int AtoiBase10(char* str);
char *ItoaBase10(int num);

void test_endian( void );
