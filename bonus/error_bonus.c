/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:16:49 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 14:27:31 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_bonus.h"

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
