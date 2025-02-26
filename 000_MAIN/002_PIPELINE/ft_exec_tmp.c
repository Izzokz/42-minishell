/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_tmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:14:26 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/02/24 16:14:28 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *cmd)
{
	return (!ft_strncmp(cmd, "echo", -1)
		|| !ft_strncmp(cmd, "cd", -1)
		|| !ft_strncmp(cmd, "pwd", -1)
		|| !ft_strncmp(cmd, "export", -1)
		|| !ft_strncmp(cmd, "unset", -1)
		|| !ft_strncmp(cmd, "env", -1)
		|| !ft_strncmp(cmd, "exit", -1));
}

static int	handle_builtins(t_data *data, t_rlines cmd)
{
	if (!ft_strncmp(cmd[0], "export", -1))
		return (ft_export(data, cmd));
	if (!ft_strncmp(cmd[0], "echo", -1))
		return (ft_echo(cmd));
	if (!ft_strncmp(cmd[0], "unset", -1))
		return (ft_unset(data, cmd));
	if (!ft_strncmp(cmd[0], "env", -1))
		return (ft_printf("%*[\n]s\n", data->envp));
	if (!ft_strncmp(cmd[0], "pwd", -1))
		return (ft_pwd());
	if (!ft_strncmp(cmd[0], "cd", -1))
		return (ft_cd(data, cmd));
	if (!ft_strncmp(cmd[0], "exit", -1))
	{
		ft_exit(data, cmd);
		return (0);
	}
	return (-1);
}

static void	ft_redirec(t_data *data)
{
	if (data->input_fd >= 0)
		dup2(data->input_fd, 0);
	else if (data->prevpipe != -1)
		dup2(data->pipe[0], 0);
	if (data->output_fd >= 0)
		dup2(data->output_fd, 1);
	else if (!data->endpipe)
		dup2(data->pipe[1], 1);
	if (data->input_fd >= 0)
		close(data->input_fd);
	close(data->pipe[0]);
}

int	ft_exec(t_data *data, void *cmd)
{
	char		*path;

	ft_redirec(data);
	if (is_builtin(((t_rlines)cmd)[0]))
		return (handle_builtins(data, (t_rlines)cmd));
	path = ft_get_path(((t_rlines)cmd)[0], data->path);
	if (path)
		execve(path, (t_rlines)cmd, data->envp);
	free(path);
	ft_free_all(data);
	exit(127);
}
