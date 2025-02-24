/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:40:08 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/01/29 20:40:09 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_env_var(char ***line, char *var, t_ints *info, int i)
{
	char	*output;

	if (var[0] == '?')
		return (ft_itoa(errno));
	if (!ft_is_env(var))
		return (ft_calloc(1, 1));
	output = ft_pick_env(var);
	if (!info->count2 && output && info->height >= -42 && info->tmp1 > -42)
	{
		info->j = i;
		split_space(line, &output, info);
	}
	return (output);
}

static int	remap2(char ***line, char **tmp, char **var, t_ints *j)
{
	if (!*line)
		return (sizeof(free(*var)) == sizeof(free(*tmp)));
	if (!*tmp)
		return (ft_printf_err("Internal Error:ft_calloc(%*.)", 2));
	j->k = -1;
	while (++(j->k) < j->tmp + 1)
		(*tmp)[j->k] = (**line)[j->k];
	j->k--;
	j->x = -1;
	while ((*var)[++(j->x)])
		(*tmp)[++(j->k)] = (*var)[j->x];
	free(*var);
	j->i--;
	while ((**line)[++(j->i)])
		(*tmp)[++(j->k)] = (**line)[j->i];
	free(**line);
	**line = *tmp;
	return (0);
}

int	remap(char ***line, t_ints *i)
{
	t_ints	j;
	char	*tmp;
	char	*var;

	j = (t_ints){.i = i->i, .tmp = i->i};
	while (ft_isalnum((**line)[++(j.i)]))
		;
	if (j.i == i->i + 1 && (**line)[++j.i - 1] != '?')
		return (0);
	tmp = ft_substr((**line), i->i + 1, j.i - (i->i + 1));
	if (!tmp)
		return (ft_printf_err("Internal Error:ft_substr(%*.)", 2));
	var = ft_env_var(line, tmp, i, j.i);
	free(tmp);
	tmp = NULL;
	if (!var)
		return (-1);
	if (*line)
		tmp = ft_calloc((ft_strlen(**line) - (j.i - (i->i + 1)))
				+ ft_strlen(var) + 1, 1);
	return (remap2(line, &tmp, &var, &j));
}
