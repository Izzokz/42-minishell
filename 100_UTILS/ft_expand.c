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

static void	secure_free(t_rlines *split, t_data *data, t_ints *info)
{
	t_rlines	part;

	part = *(data->input + info->tmp + info->tmp1 + info->tmp2);
	ft_printf_err("Internal Error:ft_rlines_add()", 2);
	ft_free_rlines(&part);
	ft_free_rlines(split);
	ft_free_slines(&(data->input));
}

static void	split_space2(char **line, char **var, t_ints *info)
{
	t_data		*data;
	t_rlines	split;
	int			len;

	split = ft_split(*var, ' ');
	free(*var);
	data = ft_get_tdata();
	if (!split)
		return ((void)ft_printf_err("Internal Error:ft_split()", 2));
	len = ft_rlines_len(split);
	free(*line);
	*line = split[++(info->tmp2)];
	while (++(info->tmp2) < len)
		if (ft_rlines_add(&(data->input[info->tmp]), split[info->tmp2],
				info->tmp1 + info->tmp2) == -1)
			return (secure_free(&split, data, info));
}

static void	split_space(char **line, char **var, t_ints *info)
{
	char	*tmp;
	t_ints	i;

	tmp = ft_calloc(ft_strlen(*var) + 1, sizeof(char));
	if (!tmp)
		return ;
	i = (t_ints){.count = 1, .i = -1, .x = -1};
	replace_loop(var, &tmp, &i);
	free(*var);
	*var = tmp;
	info->tmp2 = -1;
	if (info->tmp >= 0 && info->tmp1 >= 0)
		return (split_space2(line, var, info));
}

static char	*ft_env_var(char **line, char *var, t_rlines envp, t_ints *info)
{
	char	*output;
	char	*temp;
	int		len;
	int		i;

	info->count = ft_is_env(var);
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
	if (!(info->count))
		return (ft_calloc(1, 1));
	if (!info->count2)
		split_space(line, &output, info);
	return (output);
}

static int	remap2(char **line, char **tmp, char **var, t_ints *i)
{
	if (((!line || !*line) && i->count && i->tmp >= 0 && i->tmp1 >= 0)
		|| !(*tmp))
		return (sizeof(free(*var)) == sizeof(free(*tmp)));
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

static int	remap(char **line, t_ints *i, t_rlines envp)
{
	t_ints	j;
	char	*tmp;
	char	*var;

	if ((*line)[i->i] != '$')
		return (0);
	j = (t_ints){.i = i->i, .tmp = i->i};
	while ((*line)[++(j.i)] && ft_isalnum((*line)[j.i]))
		;
	if (j.i - i->i - 1 <= 0)
		return (0);
	tmp = ft_substr((*line), i->i + 1, j.i - i->i - 1);
	if (!tmp)
		return (ft_printf_err("Internal Error:ft_substr(%*.)", 2));
	var = ft_env_var(line, tmp, envp, i);
	free(tmp);
	tmp = NULL;
	if (!var)
		return (-1);
	if (line && *line)
		tmp = ft_calloc((ft_strlen(*line) - (j.i - i->i))
				+ ft_strlen(var) + 1, 1);
	i->i += ft_strlen(var) - 1;
	return (remap2(line, &tmp, &var, &j));
}

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
int	ft_expand_line(char **input, int parent_i, int old_parent_i, t_rlines envp)
{
	t_ints	i;

	i = (t_ints){.i = -1, .count1 = 0, .count2 = 0,
		.tmp = old_parent_i, .tmp1 = parent_i};
	while ((*input)[++(i.i)])
	{
		i.tmp = count_skip(input, &i);
		if (i.tmp == -1)
			return (-1);
		if (i.tmp)
			continue ;
		if (remap(input, &i, envp) == -1)
			return (ft_printf_err("Internal Error%*.", 2));
		if (!input || !(*input))
			break ;
	}
	return (0);
}
