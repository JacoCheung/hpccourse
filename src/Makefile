#Mikefile

OPT = -O2
LIBPATH =../lib
MYLIB = mympi
LIBMYMPI = libmympi.a
LIBOBJS = mybegin.o myend.o ring.o datatype.o mpistruct.o rcmatmul.o mesh.o scan.o
CC = mpicc
CFLAG = -I../include
%.o: %.c
	$(CC) -c $(OPT)  $(CFLAG) -o $@ $<

#ultimate target
main: main.o mylib
	$(CC) $(OPT) $(CFLAG) -o $@ $< -L$(LIBPATH) -l$(MYLIB) -lm 
	mv main ../bin
	rm *.o
		
#make a library
mylib: $(LIBOBJS)
		ar rcs $(LIBMYMPI) $(LIBOBJS)
		mv $(LIBMYMPI) ../lib
 
exam:exam1.c exam2.c
	$(CC) -o exam1 $(CFLAG) exam1.c
	$(CC) -o exam2 $(CFLAG) exam2.c
.PHONY = clean
clean:
		rm -f *.o *.a a.out main exam2 exam1 ../lib/*
