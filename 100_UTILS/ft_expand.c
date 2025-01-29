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

static char	*ft_env_var(char *var, t_rlines envp)
{
	char	*path_line;
	char	*temp;
	int		len;
	int		i;

	temp = gnlxio_ft_strjoinfree(&(char *){ft_strdup(var)},
			&(char *){ft_strdup("=")});
	if (!temp)
	{
		ft_printf_err("Internal Error:ft_realloc(%*.)", 2);
		return (NULL);
	}
	path_line = NULL;
	len = ft_strlen(temp);
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], temp, len))
		{
			path_line = ft_substr(envp[i], len, -1);
			break ;
		}
	}
	free(temp);
	return (path_line);
}

static int	remap2(char **line, char **tmp, char **var, t_ints *i)
{
	if (!(*tmp))
	{
		free(*var);
		return (ft_printf_err("Internal Error:ft_calloc(%*.)", 2));
	}
	i->k = -1;
	while (++(i->k) < i->tmp)
		(*tmp)[i->k] = (*line)[i->k];
	i->k--;
	i->x = -1;
	while ((*var)[++(i->x)])
		(*tmp)[++(i->k)] = (*var)[i->x];
	free(*var);
	i->i--;
	while ((*line)[++(i->i)])
		(*tmp)[++(i->k)] = (*line)[i->i];
	free(*line);
	*line = *tmp;
	return (0);
}

static int	remap(char **line, int i, t_rlines envp)
{
	t_ints	j;
	char	*tmp;
	char	*var;

	if ((*line)[i] != '$')
		return (0);
	j.i = i;
	j.tmp = i;
	while ((*line)[++(j.i)] && (*line)[j.i] != ' ' && (*line)[j.i] != '"'
		&& (*line)[j.i] != '\"' && (*line)[j.i] != '\t')
		;
	tmp = ft_substr((*line), i + 1, j.i - i);
	if (!tmp)
		return (ft_printf_err("Internal Error:ft_substr(%*.)", 2));
	var = ft_env_var(tmp, envp);
	free(tmp);
	tmp = NULL;
	if (!var)
		return (-1);
	tmp = ft_calloc((ft_strlen(*line) - (j.i - i)) + ft_strlen(var) + 1, 1);
	return (remap2(line, &tmp, &var, &j));
}

int	ft_expand_line(char **input, t_rlines envp)
{
	int	i;

	i = -1;
	while ((*input)[++i])
		if (remap(input, i, envp) == -1)
			return (-1);
	return (0);
}

int	ft_expand_rlines(t_rlines *input, t_rlines envp)
{
	int	i;

	i = -1;
	while ((*input)[++i])
		if (ft_expand_line(&((*input)[i]), envp) == -1)
			return (-1);
	return (0);
}

int	ft_expand_slines(t_slines *input, t_rlines envp)
{
	int	i;

	i = -1;
	while ((*input)[++i])
		if (ft_expand_rlines(&((*input)[i]), envp) == -1)
			return (-1);
	return (0);
}
