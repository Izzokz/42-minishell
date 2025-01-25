/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:55:31 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/01/24 15:35:10 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	needs_fork(char *cmd)
{
	return (!ft_strnstr(cmd, "echo", -1)
		&& !ft_strnstr(cmd, "cd", -1)
		&& !ft_strnstr(cmd, "pwd", -1)
		&& !ft_strnstr(cmd, "export", -1)
		&& !ft_strnstr(cmd, "unset", -1)
		&& !ft_strnstr(cmd, "env", -1));
}

static int	handle_builtins(t_data *data, t_rlines cmd, char **path)
{
	free(*path);
/*	if (ft_strnstr(cmd[0], "echo", -1))
		return (ft_echo(data, cmd));
	if (ft_strnstr(cmd[0], "cd", -1))
		return (ft_cd(data, cmd));
	if (ft_strnstr(cmd[0], "pwd", -1))
		return (ft_pwd(data, cmd));
	if (ft_strnstr(cmd[0], "export", -1))
		return (ft_export(data, cmd));
	if (ft_strnstr(cmd[0], "unset", -1))
		return (ft_unset(data, cmd));
	if (ft_strnstr(cmd[0], "env", -1))
		return (ft_env(data, cmd));*/
	if (ft_strnstr(cmd[0], "exit", -1))
		ft_exit(data, cmd);
	return (-1);
}

int	ft_exec(t_data *data, t_rlines cmd)
{
	int		pid;
	char	*path;

	path = ft_get_path(cmd[0], data->path);
	if (needs_fork(cmd[0]))
		pid = fork();
	else
		return (handle_builtins(data, cmd, &path));
	if (pid < 0)
		return (ft_printf_err("Internal Error:fork(%*.)", 2));
	if (pid == 0)
	{
		if (path && data->exe && ft_strnstr(cmd[0], "exit", -1))
			execve(path, cmd, data->envp);
		else if (data->exe && ft_strnstr(cmd[0], "exit", -1))
			return (handle_builtins(data, cmd, &path));
		free(path);
		ft_free_all(data);
		exit(127);
	}
	free(path);
	return (0);
}
