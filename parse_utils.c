/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:41:50 by yakim             #+#    #+#             */
/*   Updated: 2024/04/09 17:02:08 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"

void	free_split(char **arr)
{
	char	**temp;

	temp = arr;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(arr);
}