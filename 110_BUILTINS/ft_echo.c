/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:22:15 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/28 19:00:43 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_rlines cmd)
{
	t_ints	ints;

	ints.count = 0;
	ints.len = ft_rlines_len(cmd);
	if (ints.len == 1)
		return (ft_printf("\n"));
	ints.i = 1;
	if (!ft_strncmp("-n", cmd[1], 2))
	{
		ints.count = 1;
		ints.i++;
	}
	ft_printf("%*[ ]s", cmd + ints.i);
	if (ints.count == 0)
		ft_printf("\n");
	return (0);
}
