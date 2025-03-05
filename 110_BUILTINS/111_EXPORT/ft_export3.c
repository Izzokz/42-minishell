/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:52:47 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/26 17:41:03 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_name(char *name)
{
    if (!name || !isalpha(name[0]) && name[0] != '_')
        return (0);
    for (int i = 1; name[i]; i++)
    {
        if (!isalnum(name[i]) && name[i] != '_')
            return (0);
    }
    return (1);
}

int	ft_chr(char *cmd)
{
    int	i;

    if (ft_isdigit(cmd[0]) || !is_valid_var_name(cmd))
        return (-1);
    i = -1;
    while (cmd[++(i)])
    {
        if (cmd[i] == '+' && cmd[i + 1] == '=')
            return (i + 1);
        if (cmd[i] == '=')
            return (i);
    }
    return (0);
}

void	ft_print_var(t_rlines var)
{
    t_ints	num;

    num.i = -1;
    while (var[++(num.i)])
    {
        num = (t_ints){.i = num.i, .j = -1, .tmp = 0};
        ft_printf("declare -x ");
        while (var[num.i][++(num.j)])
        {
            ft_printf("%c", var[num.i][num.j]);
            if (var[num.i][num.j] == '=')
            {
                num.tmp = 1;
                ft_printf("\"");
                break ;
            }
        }
        if (num.tmp)
            ft_printf("%s\"\n", var[num.i] + num.j + 1);
        else
            ft_printf("\n");
    }
}
