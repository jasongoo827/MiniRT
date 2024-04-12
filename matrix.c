#include "matrix.h"

t_matrix	*alloc_matrix(void)
{
	t_matrix	*matrix;

	null_check(matrix = (t_matrix *)malloc(sizeof(t_matrix)));
	return (matrix);
}

t_matrix	*init_look_at_matrix(t_vector *eye_position, t_vector *r0, \
t_vector *r1, t_vector *r2)
{
	t_matrix	*l_matrix;

	l_matrix = alloc_matrix();
	l_matrix->d[0][0] = r0->d[X];
	l_matrix->d[1][0] = r0->d[Y];
	l_matrix->d[2][0] = r0->d[Z];
	l_matrix->d[0][1] = r1->d[X];
	l_matrix->d[1][1] = r1->d[Y];
	l_matrix->d[2][1] = r1->d[Z];
	l_matrix->d[0][2] = r2->d[X];
	l_matrix->d[1][2] = r2->d[Y];
	l_matrix->d[2][2] = r2->d[Z];
	l_matrix->d[0][3] = 0;
	l_matrix->d[1][3] = 0;
	l_matrix->d[2][3] = 0;
	l_matrix->d[3][0] = -dot(eye_position, r0);
	l_matrix->d[3][1] = -dot(eye_position, r1);
	l_matrix->d[3][2] = -dot(eye_position, r2);
	l_matrix->d[3][3] = 1;
	return (l_matrix);
}

t_matrix	*get_look_at_matrix(t_camera *camera)
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
	normalize_vector(&eye_direction); // r2
	cross(&r0, &eye_direction, &up_direction);
	normalize_vector(&r0);
	camera->horizontal = vec4(-r0.d[X], -r0.d[Y], -r0.d[Z], r0.d[W]);
	cross(&r1, &eye_direction, &r0);
	normalize_vector(&r1);
	camera->vertical = vec4(-r1.d[X], -r1.d[Y], -r1.d[Z], r1.d[W]);
	return (init_look_at_matrix(&camera->origin, &r0, &r1, &eye_direction));
}
