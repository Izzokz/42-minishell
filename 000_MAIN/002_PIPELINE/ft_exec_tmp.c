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

static void	ft_redirec2(int saveio[2], int is_builtin)
{
	if (is_builtin == 2)
	{
		dup2(saveio[0], 0);
		dup2(saveio[1], 1);
	}
	close(saveio[0]);
	close(saveio[1]);
}

static void	ft_redirec(t_data *data, int is_builtin)
{
	static int	saveio[2];

	if (is_builtin >= 2)
		return (ft_redirec2(saveio, is_builtin));
	if (is_builtin == 1)
	{
		saveio[0] = dup(0);
		saveio[1] = dup(1);
	}
	if (data->input_fd >= 0)
		dup2(data->input_fd, 0);
	else if (data->prevpipe != -1 && !is_builtin)
		dup2(data->prevpipe, 0);
	if (data->output_fd >= 0)
		dup2(data->output_fd, 1);
	else if (!data->endpipe && !is_builtin)
		dup2(data->pipe[1], 1);
	if (!is_builtin)
	{
		if (data->pipe[0] >= 0)
			close(data->pipe[0]);
		if (data->pipe[1] >= 0)
			close(data->pipe[1]);
	}
}

static int	handle_builtins(t_data *data, t_rlines cmd)
{
	int		ret;

	ret = 0;
	if (!ft_strncmp(cmd[0], "export", -1))
		ret = ft_export(data, cmd);
	else if (!ft_strncmp(cmd[0], "echo", -1))
		ret = ft_echo(cmd);
	else if (!ft_strncmp(cmd[0], "unset", -1))
		ret = ft_unset(data, cmd);
	else if (!ft_strncmp(cmd[0], "env", -1))
		ret = ft_printf("%*[\n]s\n", data->envp);
	else if (!ft_strncmp(cmd[0], "pwd", -1))
		ret = ft_pwd();
	else if (!ft_strncmp(cmd[0], "cd", -1))
		ret = ft_cd(data, cmd);
	else if (!ft_strncmp(cmd[0], "exit", -1))
	{
		ft_redirec(data, 3);
		ft_exit(data, cmd);
		return (0);
	}
	ft_redirec(data, 2);
	return (ret);
}

int	ft_exec(t_data *data, void *cmd)
{
	char		*path;

	if (is_builtin(((t_rlines)cmd)[0]))
	{
		ft_redirec(data, 1);
		return (handle_builtins(data, (t_rlines)cmd));
	}
	ft_redirec(data, 0);
	path = ft_get_path(((t_rlines)cmd)[0], data->path);
	if (path)
		execve(path, (t_rlines)cmd, data->envp);
	free(path);
	ft_free_all(data);
	exit(127);
}
