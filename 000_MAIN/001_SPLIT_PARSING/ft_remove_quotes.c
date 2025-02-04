/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:21:15 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/01/27 19:21:17 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	del_index(char **part, int *i)
{
	t_ints	j;
	char	*tmp;

	tmp = ft_calloc(ft_strlen(*part), sizeof(char));
	if (!tmp)
		return (-1);
	j.i = -1;
	j.j = -1;
	while ((*part)[++(j.i)])
		if (j.i != *i)
			tmp[++(j.j)] = (*part)[j.i];
	if ((*part)[*i] != '\\')
		(*i)--;
	free(*part);
	*part = tmp;
	return (0);
}

static int	remove_quotes(char **part)
{
	t_ints	i;

	i.i = -1;
	i.count1 = 0;
	i.count2 = 0;
	while ((*part)[++(i.i)])
	{
		if (!i.count2 && (*part)[i.i] == '\'')
			i.count1 = !i.count1;
		else if (!i.count1 && (*part)[i.i] == '"')
			i.count2 = !i.count2;
		if ((!i.count1 && (((*part)[i.i] == '\\'
					&& (*part)[i.i + 1] == '"')
			|| (*part)[i.i] == '"'))
			|| (!i.count2 && (*part)[i.i] == '\''))
			if (del_index(part, &i.i) == -1)
				return (-1);
	}
	return (0);
}

int	ft_remove_quotes(t_slines input)
{
	t_ints	i;

	i.i = -1;
	while (input[++(i.i)])
	{
		i.j = -1;
		while (input[i.i][++(i.j)])
			if (remove_quotes(&(input[i.i][i.j])) == -1)
				return (-1);
	}
	return (0);
}
