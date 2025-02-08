/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:01:50 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/08 17:04:03 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_env(t_data *data, t_ints *num)
{
	num->i = 0;
	num->j = 0;
	num->k = 0;
	while (data->envp[num->i])
	{
		if (!ft_strncmp(data->envp[num->i], "HOME=", 5))
			break ;
		num->i++;
	}
	while (data->envp[num->j])
	{
		if (!ft_strncmp(data->envp[num->j], "PWD=", 4))
			break ;
		num->j++;
	}
	while (data->envp[num->k])
	{
		if (!ft_strncmp(data->envp[num->k], "OLDPWD=", 7))
			break ;
		num->k++;
	}
}

static void	ft_cd_no_args(t_data *data, t_ints i)
{
	char	*path;

	path = ft_substr(data->envp[i.i], 5, -1);
	if (path)
	{
		chdir(path);
		free(path);
	}
	path = ft_substr(data->envp[i.j], 4, -1);
	free(data->envp[i.k]);
	data->envp[i.k] = gnlxio_ft_strjoinfree(&(char *){ft_strdup("OLDPWD=")},
			&path);
	path = ft_substr(data->envp[i.i], 5, -1);
	free(data->envp[i.j]);
	data->envp[i.j] = gnlxio_ft_strjoinfree(&(char *){ft_strdup("PWD=")},
			&path);
}

static void	ft_cd_reverse(t_data *data, t_ints i)
{
	char	*path;
	char	*pwd;

	path = ft_substr(data->envp[i.k], 7, -1);
	pwd = NULL;
	if (path)
	{
		chdir(path);
		pwd = ft_strdup(path);
		free(path);
	}
	path = ft_substr(data->envp[i.j], 4, -1);
	free(data->envp[i.k]);
	data->envp[i.k] = gnlxio_ft_strjoinfree(&(char *){ft_strdup("OLDPWD=")},
			&path);
	free(data->envp[i.j]);
	ft_printf("%s\n", pwd);
	data->envp[i.j] = gnlxio_ft_strjoinfree(&(char *){ft_strdup("PWD=")},
			&pwd);
}

static void	ft_cd_with_path(t_data *data, t_ints i, t_rlines cmd)
{
	char	*path;

	if (chdir(cmd[1]) != -1)
	{
		path = ft_substr(data->envp[i.j], 4, -1);
		free(data->envp[i.k]);
		data->envp[i.k] = gnlxio_ft_strjoinfree(&(char *){ft_strdup("OLDPWD=")},
				&path);
		path = getcwd(NULL, 0);
		free(data->envp[i.j]);
		data->envp[i.j] = gnlxio_ft_strjoinfree(&(char *){ft_strdup("PWD=")},
				&path);
		return ;
	}
	ft_printf_fd("\e[1;31m[Minishell] \e[0;97mNo such file or directory\e[0m\n",
		2);
}

int	ft_cd(t_data *data, t_rlines cmd)
{
	t_ints		i;

	ft_get_env(data, &i);
	i.len = ft_rlines_len(cmd);
	if (i.len > 2)
		return (ft_printf_fd("\e[1;31m[Minishell] \e[0;97mtoo many args\e[0m\n",
				2));
	else if (i.len == 1)
		ft_cd_no_args(data, i);
	else
	{
		if (cmd[1][0] == '-' && ft_strlen(cmd[1]) == 1)
			ft_cd_reverse(data, i);
		else
			ft_cd_with_path(data, i, cmd);
	}
	return (0);
}
