/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_slines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:59:20 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/02/15 16:58:46 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_expand_rlines(t_rlines *input, t_ints *info)
{
	*info = (t_ints){.height = info->height, .tmp1 = -1, .i = -1};
	while ((*input)[++(info->tmp1)])
	{
		if (ft_expand_line(&((*input)[info->tmp1]), info) == -1)
			return (-1);
		*input = ((t_data *)ft_get_tdata())->input[info->height];
	}
	return (0);
}

/*
In the whole expand function set:
info.tmp relates to count_skip()'s return
info.height is the position in slines
info.tmp1 is the position in rlines
info.i is the position in a string
info.j is a temporary index to save the end of a string when splitting
info.count1 is used to handle single quotes
info.count2 is used to handle double quotes
info.tmp2 is used to cross split in split_space2()
*/
int	ft_expand_slines(t_slines *input)
{
	t_ints	info;

	info.height = -1;
	while ((*input)[++info.height])
	{
		if (ft_expand_rlines(&((*input)[info.height]), &info) == -1)
			return (-1);
		*input = ((t_data *)ft_get_tdata())->input;
	}
	return (0);
}
