#include <stdio.h>
#include "ws5.h"

int main(int argc, char *argv[])
{
	char *filename = argv[1];
	Functions functions  [NUMOPFUNCTIONS];
	InitializesTheStructure(functions );
	ErrorOpenFile(filename);
	printf("write what u wont\n");
	UserSelection(filename, functions );
	
	(void)argc;
	
	return 0;
}
