#include "matrix.h"

t_vector	*alloc_vector(double x, double y, double z, double w)
{
	t_vector	*vector;

	null_check(vector = (t_vector *)malloc(sizeof(t_vector)));
	vector->d[X] = x;
	vector->d[Y] = y;
	vector->d[Z] = z;
	vector->d[W] = w;
	return (vector);
}

t_vector	vec4(double x, double y, double z, double w)
{
	t_vector	vector;

	vector.d[X] = x;
	vector.d[Y] = y;
	vector.d[Z] = z;
	vector.d[W] = w;
	return (vector);
}

void	normalize_vector(t_vector *vector)
{
	double	size;

	size = sqrt(pow(vector->d[0], 2) + pow(vector->d[1], 2) \
	+ pow(vector->d[2], 2));
	vector->d[0] /= size;
	vector->d[1] /= size;
	vector->d[2] /= size;
}

void	cross(t_vector *ret, t_vector *v1, t_vector *v2)
{
	ret->d[X] = v1->d[Y] * v2->d[Z] - v1->d[Z] * v2->d[Y];
	ret->d[Y] = v1->d[Z] * v2->d[X] - v1->d[X] * v2->d[Z];
	ret->d[Z] = v1->d[X] * v2->d[Y] - v1->d[Y] * v2->d[X];
}

double	dot(t_vector *v1, t_vector *v2)
{
	double		x;
	double		y;
	double		z;

	x = v1->d[X] * v2->d[X];
	y = v1->d[Y] * v2->d[Y];
	z = v1->d[Z] * v2->d[Z];
	return (x + y + z);
}