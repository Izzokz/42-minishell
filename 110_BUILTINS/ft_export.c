/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:30:08 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/30 05:08:14 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_chr(char *cmd)
{
	t_ints i;

	i.i = -1;
	while (cmd[++i.i])
		if (cmd[i.i] == '=')
			return (1);
	return (0);
}

int	ft_export(t_data *data, t_rlines cmd)
{
	t_ints ints;

	ints.len = ft_rlines_len(cmd);
	if (ints.len == 1)
		return (ft_printf_fd("\e[1;31m[Minishell] \e[0;97mnot enough arguments\e[0m\n", 2));
	ints.i = 0;
	while (cmd[++ints.i])
	{
		if (!ft_chr(cmd[ints.i]))
			ft_rlines_add(&data->envp, cmd[ints.i], A_END);
		else
			ft_printf_fd("\e[1;31m[Minishell] \e[0;97mnot a valid identifier\e[0m\n", 2);
	}
	return (0);
}
