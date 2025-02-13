/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:11:57 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/02/13 10:11:57 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_env(char *var)
{
	t_rlines	envp;
	char		*lim;
	int			i;

	envp = ((t_data *)ft_get_tdata())->envp;
	lim = ft_strjoin(var, "=");
	if (!lim)
		return (ft_printf_err("Internal Error:ft_strjoin(%*.)", 2) + 1);
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
