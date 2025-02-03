/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fix_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:14:57 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/01/29 12:14:58 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_to_tmp(t_rlines *tmp, char *part)
{
	char	*dup;

	dup = NULL;
	dup = ft_strdup(part);
	if (!dup)
		return (ft_printf_err("Internal Error:ft_strdup(%*.)", 2));
	if (ft_rlines_add(tmp, dup, A_END) == -1)
		return (!!(((void *[2]){(free(dup), NULL), (void *)42}[1])) - 2);
	return (0);
}

static int	reorder(t_rlines *part, t_rlines *tmp, int pos)
{
	int	i;

	i = -1;
	while ((*part)[++i])
	{
		if (pos == 1)
			if ((*part)[i][0] == '<' && (*part)[i][1] == '<')
				if (add_to_tmp(tmp, (*part)[i]) == -1)
					return (!!ft_free_rlines(tmp) - 1);
		if (pos == 2)
			if ((*part)[i][0] == '<' && (*part)[i][1] != '<')
				if (add_to_tmp(tmp, (*part)[i]) == -1)
					return (!!ft_free_rlines(tmp) - 1);
		if (pos == 3)
			if ((*part)[i][0] != '<' && (*part)[i][0] != '>')
				if (add_to_tmp(tmp, (*part)[i]) == -1)
					return (!!ft_free_rlines(tmp) - 1);
		if (pos == 4)
			if ((*part)[i][0] == '>')
				if (add_to_tmp(tmp, (*part)[i]) == -1)
					return (!!ft_free_rlines(tmp) - 1);
	}
	return (0);
}

int	ft_fix_order(t_slines *input)
{
	int			i;
	t_rlines	tmp;

	i = -1;
	while ((*input)[++i])
	{
		tmp = ft_calloc(1, sizeof(char *));
		if (!tmp)
			return (ft_printf_err("Internal Error:ft_calloc(%*.)", 2));
		if (reorder(&((*input)[i]), &tmp, 1) == -1)
			return (-1);
		if (reorder(&((*input)[i]), &tmp, 2) == -1)
			return (-1);
		if (reorder(&((*input)[i]), &tmp, 3) == -1)
			return (-1);
		if (reorder(&((*input)[i]), &tmp, 4) == -1)
			return (-1);
		ft_free_rlines(&((*input)[i]));
		(*input)[i] = tmp;
	}
	return (0);
}
