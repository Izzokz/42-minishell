/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:22:15 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/05 14:10:49 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_check_option(t_rlines cmd, t_ints *ints)
{
    while (cmd[++ints->i])
    {
        ints->j = -1;
        while (cmd[ints->i][++ints->j])
        {
            if (cmd[ints->i][0] != '-' || (cmd[ints->i][ints->j] != 'n'
                && ints->j != 0))
                return ;
        }
        ints->count++;
    }
}

int	ft_echo(t_rlines cmd)
{
    t_ints	ints;

    ints.count = 0;
    ints.len = ft_rlines_len(cmd);
    if (ints.len == 1)
        return (ft_printf("\n"));
    ints.i = 0;
    ft_check_option(cmd, &ints);
    ft_printf("%*[ ]s", cmd + ints.i);
    if (!ints.count)
        ft_printf("\n");
    return (0);
}
