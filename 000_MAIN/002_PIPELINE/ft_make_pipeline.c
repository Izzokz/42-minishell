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

static int	ft_set_operation(t_data *data, int part)
{
	t_ints	i;

	data->pipeline[part] = ft_calloc(2, sizeof(char *));
	i.i = -1;
	i.count = 0;
	while (data->input[part][++(i.i)])
	{
		i.count++;
//		if (data->input[part][i.i][0] == '<')
//			ft_handle_input_redirection(data, part, &i);
		if (data->input[part][i.i][0] == '>')
		{
			ft_realloc_rlines(&(data->pipeline[part]), 1);
			if (!data->pipeline)
				return (ft_printf_err(
						"Internal Error:ft_realloc_rlines(%*.)", 2));
			data->pipeline[part][i.i] = ft_strdup(data->input[part][i.i]);
			if (!(data->pipeline[part][i.i]))
				return (ft_printf_err("Internal Error:ft_strdup(%*.)", 2));
			i.count = 0;
		}
	}
	return (0);
}

int	ft_make_pipeline(t_data *data)
{
	int	len;

	len = -1;
	while (data->input[++len])
		;
	data->pipeline = ft_calloc(len + 1, sizeof(t_rlines));
	if (!data->pipeline)
		return (ft_printf_err("Internal Error:ft_calloc(%*.)", 2));
	len = -1;
	while (data->pipeline && data->pipeline[++len])
		if (ft_set_operation(data, len) == -1)
			ft_free_slines(&data->pipeline);
	return (!!data->pipeline);
}
