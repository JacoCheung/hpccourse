#Mikefile

OPT = -O2
LIBPATH =.
MYLIB = mympi
LIBMYMPI = libmympi.a
LIBOBJS = mybegin.o myend.o ring.o datatype.o mpistruct.o rcmatmul.o
CC = mpicc

%.o: %.c
	$(CC) -c $(OPT) -o $@ $<

main: main.o mylib
	$(CC) $(OPT) -o main main.o -L$(LIBPATH) -l$(MYLIB) -lm
	rm *.o
		
#make a library
mylib: $(LIBOBJS)
		ar rcs $(LIBMYMPI) $(LIBOBJS)
 
exam:exam1.c exam2.c
	$(CC) -o exam1 exam1.c
	$(CC) -o exam2 exam2.c
.PHONY = clean
clean:
		rm -f *.o *.a a.out main exam2 exam1
