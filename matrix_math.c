#include "matrix.h"

t_matrix	*alloc_matrix(void)
{
	t_matrix	*matrix;

	matrix = (t_matrix *)malloc(sizeof(t_matrix));
	return (matrix);
}