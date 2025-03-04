/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_tmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:36:43 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/02/25 11:36:44 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_pipeline_tab_len(t_pipeline **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		;
	return (i);
}

static int	ft_execute_pipeline(t_pipeline *pl)
{
	t_pipeline	*tmp;

	tmp = pl;
	while (tmp)
	{
		signal(SIGPIPE, SIG_IGN);
		if (tmp->func((t_data *)ft_get_tdata(), tmp->param) == -1)
			return (-1);
		signal(SIGPIPE, SIG_DFL);
		tmp = tmp->next;
	}
	return (0);
}

/*
bcase is set to 1 when there's no pipe
and the command is a builtin
*/
static int	handle_bcase(t_pipeline *pipeline)
{
	char		*cmd;
	t_pipeline	*tmp;
	t_data		*data;

	data = (t_data *)ft_get_tdata();
	tmp = pipeline;
	while (tmp->next)
		tmp = tmp->next;
	cmd = ((t_rlines)tmp->param)[0];
	if (!ft_strncmp(cmd, "export", -1) || !ft_strncmp(cmd, "env", -1)
		|| !ft_strncmp(cmd, "unset", -1) || !ft_strncmp(cmd, "echo", -1)
		|| !ft_strncmp(cmd, "cd", -1) || !ft_strncmp(cmd, "pwd", -1)
		|| !ft_strncmp(cmd, "exit", -1))
		data->bcase = 1;
	else
		data->bcase = 0;
	return (data->bcase);
}

static void	ft_pipe_swap(int tube[2], int *prev, t_ints i)
{
	close(tube[1]);
	if (*prev != -1)
		close(*prev);
	if (i.i < i.len - 1)
		*prev = tube[0];
	else if (tube[0] >= 0)
		close(tube[0]);
}

int	ft_loop(t_data *data)
{
	t_ints	i;

	i = (t_ints){.len = ft_pipeline_tab_len(data->pipeline), .i = -1};
	if (i.len == 1 && handle_bcase(data->pipeline[0]))
		return (ft_execute_pipeline(data->pipeline[0]));
	data->prevpipe = -1;
	while (data->pipeline[++i.i])
	{
		data->endpipe = i.i == i.len - 1;
		if (pipe(data->pipe) < 0)
			return (ft_printf_err("Internal Error:pipe(%*.)", 2));
		i.tmp = fork();
		if (i.tmp < 0)
			return (ft_printf_err("Internal Error:fork(%*.)", 2));
		if (i.tmp == 0)
		{
			ft_execute_pipeline(data->pipeline[i.i]);
			ft_free_all(data);
			exit(errno);
		}
		ft_pipe_swap(data->pipe, &data->prevpipe, i);
	}
	while (waitpid(-1, &i.tmp1, 0) > 0)
		errno = WEXITSTATUS(i.tmp1);
	return (0);
}
