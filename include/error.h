/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:08:15 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/23 19:08:16 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "essential.h"

# define MALLOC_ERR "Memory Allocation Failed!\n"

// error.c
void	null_check(void *ptr);
void	cus_error(char *message);

#endif