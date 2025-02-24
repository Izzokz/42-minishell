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

static int	del_index(char **part, int *i)
{
	t_ints	j;
	char	*tmp;

	tmp = ft_calloc(ft_strlen(*part), sizeof(char));
	if (!tmp)
		return (ft_printf_err("Internal Error:ft_calloc(%*.)", 2));
	j = (t_ints){.i = -1, .j = -1};
	while ((*part)[++(j.i)])
		if (j.i != *i)
			tmp[++(j.j)] = (*part)[j.i];
	if ((*part)[*i] != '\\')
		(*i)--;
	free(*part);
	*part = tmp;
	return (0);
}

static int	count_skip(char **line, t_ints *i)
{
	if (i->tmp1 != 42 && !(i->count2) && (*line)[i->i] == '\'')
	{
		if (del_index(line, &(i->i)) == -1)
			return (-1);
		while ((*line)[++(i->i)] && (*line)[i->i] != '\'')
			;
		if (del_index(line, &(i->i)) == -1)
			return (-1);
		return (1);
	}
	else if (i->tmp1 != 42 && (*line)[i->i] == '\\' && ((*line)[i->i + 1] == '"'
			|| (*line)[i->i + 1] == '\\'))
	{
		if (del_index(line, &(i->i)) == -1)
			return (-1);
		return (1);
	}
	else if (i->tmp1 != 42 && (*line)[i->i] == '"')
	{
		i->count2 = !(i->count2);
		if (del_index(line, &(i->i)) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

/*
i.count1 determines if a single quote is opened
i.count2 determines if a double quote is opened
*/
int	ft_expand_line(char **input, t_ints *info)
{
	info->count1 = 0;
	info->count2 = 0;
	if (info->i == -1 && (*input)[info->i + 1] == '<'
		&& (*input)[info->i + 2] == '<')
		return (0);
	while ((*input)[++(info->i)])
	{
		info->tmp = count_skip(input, info);
		if (info->tmp == -1)
			return (ft_printf_err("Internal Error%*.", 2));
		if (!(info->tmp))
			if ((*input)[info->i] == '$' && (ft_isalnum((*input)[info->i + 1])
					|| (*input)[info->i + 1] == '?')
				&& del_index(input, &(info->i)) != -1)
				if (remap(&input, info) == -1)
					return (ft_printf_err("Internal Error%*.", 2));
		if (!input)
			break ;
		else if (!(*input)[info->i + 1])
		{
			info->i = -1;
			break ;
		}
	}
	return (0);
}

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
