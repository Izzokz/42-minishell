/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:11:57 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/03/13 14:48:35 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_var(char *var, char **envp)
{
	char	*lim;
	int		i;

	lim = ft_strjoin(var, "=");
	if (!lim)
		return (ft_printf_err(ERROR_IE"ft_strjoin(%*.)", 2) + 1);
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], lim, 5))
		{
			free(lim);
			return (1);
		}
	}
	free(lim);
	return (0);
}

char	*ft_pick_env(char *var)
{
	t_rlines	envp;
	char		*lim;
	t_ints		num;

	envp = ((t_data *)ft_get_tdata())->envp;
	lim = ft_strjoin(var, "=");
	if (!lim)
	{
		ft_printf_err(ERROR_IE"ft_strjoin(%*.)", 2);
		return (NULL);
	}
	num.i = -1;
	num.len = ft_strlen(lim);
	while (envp[++num.i])
	{
		if (!ft_strncmp(envp[num.i], lim, num.len))
		{
			free(lim);
			lim = ft_substr(envp[num.i], num.len, -1);
			return (lim);
		}
	}
	free(lim);
	return (NULL);
}

int	ft_is_env(char *var)
{
	t_rlines	envp;
	char		*lim;
	t_ints		num;

	envp = ((t_data *)ft_get_tdata())->envp;
	lim = ft_strjoin(var, "=");
	if (!lim)
		return (ft_printf_err(ERROR_IE"ft_strjoin(%*.)", 2) + 1);
	num.i = -1;
	num.len = ft_strlen(lim);
	while (envp[++num.i])
	{
		if (ft_strnstr(envp[num.i], lim, num.len))
		{
			free(lim);
			return (1);
		}
	}
	free(lim);
	return (0);
}

void	ft_modify_env(t_data *data, char *env, char *value)
{
	char	*lim;
	t_ints	num;

	lim = ft_strjoin(env, "=");
	if (!lim)
	{
		ft_printf_err(ERROR_IE"ft_strjoin(%*.)", 2);
		return ;
	}
	num.len = ft_strlen(lim);
	num.i = -1;
	while (data->envp[++num.i])
	{
		if (ft_strnstr(data->envp[num.i], lim, num.len))
		{
			free(data->envp[num.i]);
			data->envp[num.i] = gnlxio_ft_strjoinfree(&lim,
				&(char *){ft_strdup(value)});
			return ;
		}
	}
}
