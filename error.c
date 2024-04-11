/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:16:49 by yakim             #+#    #+#             */
/*   Updated: 2024/04/09 20:17:03 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	null_check(void *ptr)
{
	if (ptr == NULL)
	{
		ft_putstr_fd(MALLOC_ERR, 2);
		exit (1);
	}
}

void	cus_error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}
