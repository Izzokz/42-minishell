/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:55:31 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/02/08 13:51:38 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	needs_fork(char *cmd, t_data *data)
{
	return ((ft_strncmp(cmd, "echo", -1)
			&& ft_strncmp(cmd, "cd", -1)
			&& ft_strncmp(cmd, "pwd", -1)
			&& ft_strncmp(cmd, "export", -1)
			&& ft_strncmp(cmd, "unset", -1)
			&& ft_strncmp(cmd, "env", -1))
		&& (ft_strncmp(cmd, "exit", -1)
			|| ft_slines_rlen(data->input) > 1));
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

int	ft_exec(t_data *data, t_rlines cmd)
{
	int		pid;
	char	*path;

	if (needs_fork(cmd[0], data))
		pid = fork();
	else
		return (handle_builtins(data, cmd));
	if (pid < 0)
		return (ft_printf_err("Internal Error:fork(%*.)", 2));
	if (pid == 0)
	{
		path = ft_get_path(cmd[0], data->path);
		if (path && ft_strncmp(cmd[0], "exit", -1))
			execve(path, cmd, data->envp);
		else if (!ft_strncmp(cmd[0], "exit", -1))
			return (handle_builtins(data, cmd));
		free(path);
		ft_free_all(data);
		exit(127);
	}
	return (0);
}
