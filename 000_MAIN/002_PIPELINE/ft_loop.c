/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:25:45 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/01/24 16:25:46 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pipe_swap(int tube[2], int *prev_tube, int terminate)
{
	close(tube[1]);
	if (*prev_tube != -1)
		close(*prev_tube);
	if (terminate)
		return ;
	*prev_tube = tube[0];
}

static int	handle_direc(t_data *data, char *redirec)
{
	(void)redirec;
	(void)data;
	data->exe = 1;
	return (0);
}

int	ft_loop(t_data *data)
{
	t_ints	i;

	i.i = -1;
	data->swap_pipe = -1;
	while (data->input[++(i.i)])
	{
		i.j = -1;
		while (data->input[i.i][++(i.j)])
		{
			if (handle_direc(data, data->input[i.i][i.j]))
				continue ;
			if (pipe(data->pipe) < 0)
				return (ft_printf_err("Internal Error:pipe(%*.)", 2));
			if (ft_exec(data, *(data)->input) == -1)
				return (-1);
			ft_pipe_swap(data->pipe, &data->swap_pipe, 1);
		}
	}
	ft_pipe_swap(data->pipe, &data->swap_pipe, 1);
	while (wait(NULL) > 0)
		;
	return (0);
}
