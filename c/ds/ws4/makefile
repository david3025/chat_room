GD = gcc -ansi -pedantic-errors -Wall -Wextra -g
OBJ1 = s_list_test.o s_list.o
SRC1 = s_list_test.c s_list.c

all: depend clean prog

prog: s_list.out	

s_list.out: $(OBJ1)
		$(GD) $(OBJ1) -o s_list.out
		
s_list_test.o: 
		$(GD) -c s_list_test.c
		
s_list.o: 
		$(GD) -c s_list.c
		
depend:
		$(GD) -MM $(SRC1) >> makefile	

clean:
		rm *.o	
			
libfoo.ar : $(OBJ1) 
		ar r slist.ar $(OBJ1) s_slist.h
		

s_list_test.o: s_list_test.c s_list.h
s_list.o: s_list.c s_list.h
s_list_test.o: s_list_test.c s_list.h
s_list.o: s_list.c s_list.h
