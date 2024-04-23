#include "matrix.h"

t_matrix	*alloc_matrix(void)
{
	t_matrix	*matrix;

	null_check(matrix = (t_matrix *)malloc(sizeof(t_matrix)));
	return (matrix);
}

void		get_axis(t_camera *camera)
{
	t_vector	eye_direction;
	t_vector	up_direction;
	t_vector	r0;
	t_vector	r1;

	eye_direction = vec4(camera->dir.d[0], camera->dir.d[1], \
	camera->dir.d[2], camera->dir.d[3]);
	up_direction = vec4(0, 1, 0, 0);
	r0 = vec4(0, 0, 0, 0);
	r1 = vec4(0, 0, 0, 0);
	if (cmp_vec(eye_direction, up_direction))
	{
		if (eye_direction.d[Y] < 0)
		{
			camera->horizontal = vec4(-1, 0, 0, 0);
			camera->vertical = vec4(0, 0, -1, 0);
		}
		else
		{
			camera->horizontal = vec4(1, 0, 0, 0);
			camera->vertical = vec4(0, 0, 1, 0);
		}
		return ;
	}
	cross(&r0, &eye_direction, &up_direction);
	normalize_vector(&r0);
	camera->horizontal = vec4(r0.d[X], r0.d[Y], r0.d[Z], r0.d[W]);
	cross(&r1, &eye_direction, &r0);
	normalize_vector(&r1);
	camera->vertical = vec4(-r1.d[X], -r1.d[Y], -r1.d[Z], -r1.d[W]);
}

void mul_matrix(double a[][3], double b[][3], double result[][3])
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			result[i][j] = 0;
			k = -1;
			while (++k < 3)
				result[i][j] += a[i][k] * b[k][j];
		}
	}
}

void mul_matrix_by_constant(double matrix[][3], double constant)
{
	int	i;
	int	j;

	i = -1;
    while (++i < 3)
	{
		j = -1;
        while (++j < 3)
            matrix[i][j] *= constant;
    }
}

double (*add_matrix(double matrix1[][3], double matrix2[][3]))[3]
{
	int				i;
	int				j;
	static double	result[3][3];

	i = -1;
    while (++i < 3)
	{
		j = -1;
        while (++j < 3)
            result[i][j] = matrix1[i][j] + matrix2[i][j];
    }
	return (result);
}

t_vector convert(t_vector point, double mat[][3])
{
	t_vector	vec;
	int			i;
	int			j;

	i = -1;
	while (++i < 3)
	{
		vec.d[i] = 0;
		j = -1;
		while (++j < 3)
			vec.d[i] += mat[i][j] * point.d[j];
    }
	vec.d[W] = 0;
	return (vec);
}

void	init_k(double k[3][3], t_vector new_axis)
{
	k[0][0] = 0;
	k[0][1] = -new_axis.d[Z];
	k[0][2] = new_axis.d[Y];
	k[1][0] = new_axis.d[Z];
	k[1][1] = 0;
	k[1][2] = -new_axis.d[X];
	k[2][0] = -new_axis.d[Y];
	k[2][1] = new_axis.d[X];
	k[3][2] = 0;
}

void	init_i(double i[3][3])
{
	i[0][0] = 1;
	i[0][1] = 0;
	i[0][2] = 0;
	i[1][0] = 0;
	i[1][1] = 1;
	i[1][2] = 0;
	i[2][0] = 0;
	i[2][1] = 0;
	i[2][2] = 1;
}

// t_matrix	*init_look_at_matrix(t_vector *eye_position, t_vector *r0, \
// t_vector *r1, t_vector *r2)
// {
// 	t_matrix	*l_matrix;

// 	l_matrix = alloc_matrix();
// 	l_matrix->d[0][0] = r0->d[X];
// 	l_matrix->d[1][0] = r0->d[Y];
// 	l_matrix->d[2][0] = r0->d[Z];
// 	l_matrix->d[0][1] = r1->d[X];
// 	l_matrix->d[1][1] = r1->d[Y];
// 	l_matrix->d[2][1] = r1->d[Z];
// 	l_matrix->d[0][2] = r2->d[X];
// 	l_matrix->d[1][2] = r2->d[Y];
// 	l_matrix->d[2][2] = r2->d[Z];
// 	l_matrix->d[0][3] = 0;
// 	l_matrix->d[1][3] = 0;
// 	l_matrix->d[2][3] = 0;
// 	l_matrix->d[3][0] = -dot(eye_position, r0);
// 	l_matrix->d[3][1] = -dot(eye_position, r1);
// 	l_matrix->d[3][2] = -dot(eye_position, r2);
// 	l_matrix->d[3][3] = 1;
// 	return (l_matrix);
// }