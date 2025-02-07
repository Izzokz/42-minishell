/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:01:50 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/07 14:35:12 by pboucher         ###   ########.fr       */
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

int	ft_cd(t_data *data, t_rlines cmd)
{
	char		*path;
	char		*path2;
	char		*temp;
	t_ints		i;

	ft_get_env(data, &i);
	i.len = ft_rlines_len(cmd);
	if (i.len > 2)
		return (ft_printf_fd("\e[1;31m[Minishell] \e[0;97mtoo many args\e[0m\n", 2));
	if (i.len == 1)
	{
		path = ft_substr(data->envp[i.i], 5, -1);
		chdir(path);
	}
	if (i.len == 2)
	{
		if (cmd[1][0] == '.' && ft_strlen(cmd[1]) == 1)
			return (0);
		else if (!ft_strncmp("-", cmd[1], ft_strlen(cmd[1])))
			path = ft_substr(data->envp[i.k], 7, -1);
		else
		{
			path = gnlxio_ft_strjoinfree(&(char *){ft_strdup("/")}, &(char *){ft_strdup(cmd[1])});
			path = gnlxio_ft_strjoinfree(&(char *){ft_strdup(data->envp[i.j])}, &path);
			path2 = ft_strdup(path);
			free(path);
			path = ft_substr(path2, 4, -1);
			free(path2);
		}
		if (chdir(path) == -1)
			return (ft_printf_fd("\e[1;31m[Minishell] \e[0;97mNo such file or directory\e[0m\n", 2));
	}
	free(data->envp[i.k]);
	temp = ft_strdup("OLDPWD=");
	data->envp[i.k] = gnlxio_ft_strjoinfree(&temp,
			&(char *){ft_substr(data->envp[i.j], 4, -1)});
	free(data->envp[i.j]);
	data->envp[i.j] = ft_strjoin("PWD=", path);
	free(path);
	return (0);
}
