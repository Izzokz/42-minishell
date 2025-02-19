/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:36:53 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/01/24 15:21:39 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_set_cmd(t_data *data, t_ints *i)
{
	t_rlines	dup;

	dup = ft_rlines_dup(data->input + i->i + i->j);
	if (!dup)
		return (ft_printf_err("Internal Error:ft_calloc(%*.)", 2));
	if (!ft_add_pipeline(data->pipeline, ft_exec, &dup, ft_free_tab))
		data->pipeline = ft_new_pipeline(ft_exec, &dup, ft_free_tab);
	return (0);
}

static int	ft_set_redirec(t_data *data, char *filename,
	int (*func)(t_data *, void *), t_ints *i)
{
	char	*dup;

	dup = ft_strdup(filename);
	if (!dup)
		return (-1);
	if (!ft_add_pipeline(data->pipeline, func, dup, free))
		data->pipeline = ft_new_pipeline(func, dup, free);
	return (0);
}

static int	ft_set_operation(t_data *data, t_ints *i)
{
	if (data->input[i->i][i->j][0] == '<' && data->input[i->i][i->j][1] == '<')
		return (ft_set_redirec(data, data->input + i->i + i->j + 2,
				ft_here_doc, i));
	else if (data->input[i->i][i->j][0] == '<')
		return (ft_set_redirec(data, data->input + i->i + i->j + 1,
				ft_open_read, i));
	else if (data->input[i->i][i->j][0] == '>'
		&& data->input[i->i][i->j][1] == '>')
		return (ft_set_redirec(data, data->input + i->i + i->j + 2,
				ft_open_append, i));
	else if (data->input[i->i][i->j][0] == '>')
		return (ft_set_redirec(data, data->input + i->i + i->j + 1,
				ft_open_trunc, i));
	else
		return (ft_set_cmd(data, i));
	return (0);
}

int	ft_make_pipeline(t_data *data)
{
	t_ints	i;

	i.i = -1;
	while (data->input[++(i.i)])
	{
		i.j = -1;
		i.count = 0;
		while (data->input[++(i.j)])
		{
			if (ft_set_operation(data, &i) == -1)
			{
				ft_destroy_pipeline(data->pipeline);
				data->pipeline = NULL;
				break ;
			}
		}
	}
	return (!!data->pipeline - 1);
}
