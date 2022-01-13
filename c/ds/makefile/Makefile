GD = gcc -ansi -pedantic-errors -Wall -Wextra -g
OBJ1 = main.o foo.o
SRC1 = main.c foo.c

all: depend clean prog 

depend:
		$(GD) -MM $(SRC1) >> Makefile

clean:
		rm *.o	
	
prog: fooer.out	

fooer.out: $(OBJ1)
		$(GD) $(OBJ1) -o fooer.out
		
main.o: 
		$(GD) -c main.c
		
foo.o: 
		$(GD) -c foo.c
		
#libfoo.ar : $(OBJ1) 
#		ar r libfoo.ar $(OBJ1) foo.h
		

main.o: main.c foo.h
foo.o: foo.c foo.h
main.o: main.c foo.h
foo.o: foo.c foo.h
main.o: main.c foo.h
foo.o: foo.c foo.h
main.o: main.c foo.h
foo.o: foo.c foo.h
main.o: main.c foo.h
foo.o: foo.c foo.h
