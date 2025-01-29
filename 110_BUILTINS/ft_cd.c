/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:01:50 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/29 18:32:25 by pboucher         ###   ########.fr       */
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
	char		*temp;
	t_ints		i;

	(void)cmd;
	ft_get_env(data, &i);
	path = ft_substr(data->envp[i.i], 5, -1);
	free(data->envp[i.k]);
	temp = ft_strdup("OLDPWD=");
	data->envp[i.k] = gnlxio_ft_strjoinfree(&temp,
			&(char *){ft_substr(data->envp[i.j], 4, -1)});
	free(data->envp[i.j]);
	data->envp[i.j] = ft_strjoin("PWD=", path);
	chdir(path);
	free(path);
	return (0);
}
