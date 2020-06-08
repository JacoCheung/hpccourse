#include "myhead.h"

void datatype(which, newtp)
char which;
MPI_Datatype *newtp;
{
	int count = 2;
	if (which == 'c')
	{
		MPI_Type_contiguous(count, MPI_INT, newtp);
	}
	return;
}