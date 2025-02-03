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

static int	ft_chr(char *cmd)
{
	t_ints	i;

	i.i = -1;
	while (cmd[++(i.i)])
		if (cmd[i.i] == '=')
			return (1);
	return (0);
}

int	ft_export(t_data *data, t_rlines cmd)
{
	t_ints	ints;
	char	*dup;

	ints.len = ft_rlines_len(cmd);
	if (ints.len == 1)
		return (ft_printf_fd("\e[1;31m[Minishell] \e[0;97m%s\e[0m\n", 2,
				"not enough arguments"));
	ints.i = 0;
	while (cmd[++(ints.i)])
	{
		if (ft_chr(cmd[ints.i]))
		{
			dup = ft_strdup(cmd[ints.i]);
			if (!dup)
				return (ft_printf_err("Internal Error:ft_strdup(%*.)", 2));
			ft_rlines_add(&(data->envp), dup, A_END);
		}
		else
			ft_printf_fd("\e[1;31m[Minishell] \e[0;97m%s\e[0m\n", 2,
				"not a valid identifier");
	}
	return (0);
}
