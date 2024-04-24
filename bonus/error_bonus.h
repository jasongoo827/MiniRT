/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:08:15 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/24 14:30:41 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_BONUS_H
# define ERROR_BONUS_H

# include "essential_bonus.h"

# define MALLOC_ERR "Memory Allocation Failed!\n"

// error.c
void	null_check(void *ptr);
void	cus_error(char *message);

#endif