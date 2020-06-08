#Mikefile

OPT = -O2
LIBPATH = /home/liuke/HPC/hpccourse
MYLIB = mympi
LIBMYMPI = libmympi.a
LIBOBJS = mybegin.o myend.o ring.o
CC = mpicc

mybegin.o: mybegin.c
		$(CC) -c $(OPT) mybegin.c

myend.o: myend.c
		$(CC) -c $(OPT) myend.c

ring.o: ring.c
		$(CC) -c $(OPT) ring.c

main.o: main.c
		$(CC) $(OPT) -c main.c
		
main: main.o
		$(CC) $(OPT) -o main main.o -L$(LIBPATH) -l$(MYLIB) -lm
		
#make a library
mylib: $(LIBOBJS)
		ar rcs $(LIBMYMPI) $(LIBOBJS)
 
clean:
		rm -f *.o *.a a.out main
