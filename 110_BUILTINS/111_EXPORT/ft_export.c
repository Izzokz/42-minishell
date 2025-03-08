/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:30:08 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/08 10:06:33 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_execute(t_data *data, t_rlines cmd, t_ints *ints)
{
	char	*dup;

	if (ints->j >= 0)
	{
		dup = ft_substr(cmd[ints->i], 0, ints->j + 1);
		if (!dup)
			return (ft_printf_err(ERROR_IE"ft_substr(%*.)", 2));
		ft_make_export(data, cmd, ints, dup);
		dup = ft_substr(cmd[ints->i], 0, ints->j);
		if (!dup)
			return (ft_printf_err(ERROR_IE"ft_substr(%*.)", 2));
		ft_make_var(data, cmd, ints, dup);
	}
	else if (ints->j == 0)
	{
		dup = ft_substr(cmd[ints->i], 0, -1);
		if (!dup)
			return (ft_printf_err(ERROR_IE"ft_substr(%*.)", 2));
		ft_make_var(data, cmd, ints, dup);
	}
	else
		ft_printf_fd(ERROR_NVI, 2);
	return (0);
}

int	ft_export(t_data *data, t_rlines cmd)
{
	t_ints	ints;

	(void)data;
	ints.len = ft_rlines_len(cmd);
	if (ints.len == 1)
		return (ft_print_export(data));
	ints.i = 0;
	while (cmd[++(ints.i)])
	{
		ints.j = ft_chr(cmd[ints.i]);
		ft_execute(data, cmd, &ints);
	}
	return (0);
}
