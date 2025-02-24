/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 07:41:30 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/02/18 07:41:34 by kzhen-cl         ###   ########.fr       */
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

static void	split_space2(char ***line, char **var, t_ints *info)
{
	t_data		*data;
	t_rlines	split;
	int			len;

	split = ft_split(*var, ' ');
	free(*var);
	*var = NULL;
	data = ft_get_tdata();
	if (!split)
		return ((void)ft_printf_err("Internal Error:ft_split()", 2));
	*var = split[0];
	len = ft_rlines_len(split);
	split[0] = gnlxio_ft_strjoinfree(&(char *){ft_substr(**line, 0,
				info->i + 1)}, &split[0]);
	info->i = ft_strlen(split[len - 1]) - 2;
	split[len - 1] = gnlxio_ft_strjoinfree(&(split[len - 1]),
			&(char *){gnlxio_ft_strdup(**line + info->j)});
	ft_rlines_delete(&(data->input[info->tmp]), info->tmp1);
	while (++(info->tmp2) < len)
		if (ft_rlines_add(&(data->input[info->height]), split[info->tmp2],
				info->tmp1 + info->tmp2) == -1)
			return (secure_free(&split, data, info));
	info->tmp1 += len - 2;
	free(split);
	*line = NULL;
}

void	split_space(char ***line, char **var, t_ints *info)
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
	return (split_space2(line, var, info));
}
