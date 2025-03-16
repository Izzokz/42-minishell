/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:01:50 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/16 12:49:23 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_cd_no_args(t_data *data)
{
	char	*path;
	char	*pwd;
	int		check;

	path = ft_pick_env("HOME");
	if (!path)
	{
		data->err_num = 1;
		ft_printf_fd(ERROR_HNS, 2);
		return ;
	}
	chdir(path);
	pwd = ft_pick_env("PWD");
	check = ft_is_env("OLDPWD");
	if (check)
		ft_modify_env(data, "OLDPWD", pwd);
	check = ft_is_env("PWD");
	if (check)
		ft_modify_env(data, "PWD", path);
	free(pwd);
	free(path);
}

static void	ft_cd_reverse(t_data *data)
{
	char	*path;
	char	*pwd;

	path = ft_pick_env("OLDPWD");
	pwd = ft_pick_env("PWD");
	if (!path || !pwd)
	{
		ft_printf_fd(ERROR_CDR, 2);
		data->err_num = 1;
		free(pwd);
		free(path);
		return ;
	}
	chdir(path);
	ft_printf("%s\n", path);
	ft_modify_env(data, "OLDPWD", pwd);
	ft_modify_env(data, "PWD", path);
	free(pwd);
	free(path);
}

static void	ft_cd_with_path(t_data *data, t_rlines cmd)
{
	char	*path;

	if (chdir(cmd[1]) != -1)
	{
		path = ft_pick_env("PWD");
		if (path)
			ft_modify_env(data, "OLDPWD", path);
		free(path);
		path = getcwd(NULL, 0);
		if (path)
			ft_modify_env(data, "PWD", path);
		free(path);
		return ;
	}
	ft_printf_fd(ERROR_CD, 2, cmd[1]);
	data->err_num = 1;
}

int	ft_cd(t_data *data, t_rlines cmd)
{
	t_ints		i;

	data->err_num = 0;
	i.len = ft_rlines_len(cmd);
	if (i.len > 2)
		return (ft_printf_fd(ERROR_TMA"\n", 2));
	else if (i.len == 1)
		ft_cd_no_args(data);
	else
	{
		if (cmd[1][0] == '-' && ft_strlen(cmd[1]) == 1)
			ft_cd_reverse(data);
		else
			ft_cd_with_path(data, cmd);
	}
	return (0);
}
