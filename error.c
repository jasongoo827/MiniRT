# include "error.h"

void	null_check(void *ptr)
{
	if (ptr == NULL)
		ft_putstr_fd(MALLOC_ERR, 2);
	exit (1);
}