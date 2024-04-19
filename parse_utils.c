/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:41:50 by yakim             #+#    #+#             */
/*   Updated: 2024/04/19 13:23:56 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "parse.h"
#include "utils.h"

t_vector	parse_vector(char **arr, int isnorm, int ispoint, int iscolor)
{
	t_vector	v;
	int			i;

	if (arr == NULL)
		cus_error("Error\nLess arguments in vector input\n");
	i = -1;
	while (++i < 3)
	{
		v.d[i] = ft_strtod(arr[i]);
		if (iscolor)
		{
			if (v.d[i] < 0 || v.d[i] > 255)
				cus_error("Error\nColor input out of range\n");
			v.d[i] /= 255.999;
		}
	}
	if (ispoint)
		v.d[3] = 1;
	else
		v.d[3] = 0;
	if (isnorm && (pow(v.d[0], 2) + pow(v.d[1], 2) + pow(v.d[2], 2) != 1))
		cus_error("Error\nNot normalized vector input\n");
	if (arr[i])
		cus_error("Error\nMore arguments in vector input\n");
	return (v);
}
