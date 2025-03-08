/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:11:57 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/03/08 10:06:26 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int			i;
	int			len;

	envp = ((t_data *)ft_get_tdata())->envp;
	lim = ft_strjoin(var, "=");
	if (!lim)
		return (ft_printf_err(ERROR_IE"ft_strjoin(%*.)", 2) + 1);
	i = -1;
	len = ft_strlen(lim);
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], lim, len))
		{
			free(lim);
			return (1);
		}
	}
	free(lim);
	return (0);
}
