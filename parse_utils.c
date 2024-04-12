/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:41:50 by yakim             #+#    #+#             */
/*   Updated: 2024/04/12 16:39:36 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "parse.h"

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

t_vector	parse_vector(char **arr, int isnormalized, int ispoint)
{
	t_vector	v;
	int			i;

	if (arr == NULL)
		cus_error("Error\nLess arguments in vector input\n");
	i = 0;
	while (i < 3)
	{
		v.d[i] = ft_strtod(arr[i]);
		// printf("i: %f\n", v.d[i]);
		i++;
	}
	if (ispoint)
		v.d[3] = 1;
	else
		v.d[3] = 0;
	if (isnormalized && (pow(v.d[0], 2) + pow(v.d[1], 2) + pow(v.d[2], 2) != 1))
	{
		// printf("%.90f\n", pow(v.d[0], 2) + pow(v.d[1], 2)+ pow(v.d[2], 2));
		cus_error("Error\nNot normalized vector input\n");
	}
	if (arr[i])
		cus_error("Error\nMore arguments in vector input\n");
	return (v);
}
