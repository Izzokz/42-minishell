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

static void	replace_loop(char **var, char **tmp, t_ints *i)
{
	while ((*var)[++(i->i)])
	{
		if (ft_strchr(" \t\n\v\f\r", (*var)[i->i]) && !i->count)
		{
			(*tmp)[++(i->x)] = ' ';
			i->count = 1;
		}
		else if (!ft_strchr(" \t\n\v\f\r", (*var)[i->i]))
		{
			(*tmp)[++(i->x)] = (*var)[i->i];
			i->count = 0;
		}
	}
}

static void	replace_spaces(char **var)
{
	char	*tmp;
	t_ints	i;

	tmp = ft_calloc(ft_strlen(*var) + 1, sizeof(char));
	if (!tmp)
		return ;
	i.count = 1;
	i.i = -1;
	i.x = -1;
	replace_loop(var, &tmp, &i);
	if (i.x >= 0)
		tmp[i.x] -= tmp[i.x] * (tmp[i.x] == ' ');
	free(*var);
	*var = tmp;
}

static char	*ft_env_var(char *var, t_rlines envp, int quoted)
{
	char	*output;
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
	output = NULL;
	len = ft_strlen(temp);
	i = -1;
	while (!output && envp[++i])
		if (ft_strnstr(envp[i], temp, len))
			output = ft_substr(envp[i], len, -1);
	free(temp);
	if (!envp[i])
		return (ft_strdup(""));
	if (!quoted)
		replace_spaces(&output);
	return (output);
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

static int	remap(char **line, int *i, t_rlines envp, int quoted)
{
	t_ints	j;
	char	*tmp;
	char	*var;

	if ((*line)[*i] != '$')
		return (0);
	j.i = *i;
	j.tmp = *i;
	while ((*line)[++(j.i)] && ft_isalnum((*line)[j.i]))
		;
	if (j.i - *i - 1 <= 0)
		return (0);
	tmp = ft_substr((*line), *i + 1, j.i - *i - 1);
	if (!tmp)
		return (ft_printf_err("Internal Error:ft_substr(%*.)", 2));
	var = ft_env_var(tmp, envp, quoted);
	free(tmp);
	tmp = NULL;
	if (!var)
		return (-1);
	tmp = ft_calloc((ft_strlen(*line) - (j.i - *i)) + ft_strlen(var) + 1, 1);
	*i += ft_strlen(var) - 1;
	return (remap2(line, &tmp, &var, &j));
}

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

static int	count_skip(char **line, t_ints *i)
{
	if (!(i->count2) && (*line)[i->i] == '\'')
	{
		if (del_index(line, &(i->i)) == -1)
			return (-1);
		while ((*line)[++(i->i)] && (*line)[i->i] != '\'')
			;
		if (del_index(line, &(i->i)) == -1)
			return (-1);
		return (1);
	}
	else if ((*line)[i->i] == '\\' && ((*line)[i->i + 1] == '"'
			|| (*line)[i->i + 1] == '\\'))
	{
		if (del_index(line, &(i->i)) == -1)
			return (-1);
		return (1);
	}
	else if ((*line)[i->i] == '"')
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
int	ft_expand_line(char **input, t_rlines envp)
{
	t_ints	i;

	i.i = -1;
	i.count1 = 0;
	i.count2 = 0;
	while ((*input)[++(i.i)])
	{
		i.tmp = count_skip(input, &i);
		if (i.tmp == -1)
			return (-1);
		if (i.tmp)
			continue ;
		if (remap(input, &i.i, envp, i.count2) == -1)
			return (-1);
	}
	return (0);
}
