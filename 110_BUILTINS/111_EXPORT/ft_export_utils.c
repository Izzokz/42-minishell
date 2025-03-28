/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export4.c                                       :+:      :+:    :+:   */
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
	int	i;

	i = 0;
	while (name[++i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
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
		if (cmd[i] == '=')
			return (i);
	return (0);
}

void	ft_print_var(t_rlines var)
{
	t_ints	num;

	num.i = -1;
	while (var[++(num.i)])
	{
		num = (t_ints){.i = num.i, .j = -1, .tmp = 0};
		if (var[num.i][0] == '_' && var[num.i][1] == '=')
			continue ;
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

int	ft_print_export(t_data *data)
{
	char		*max;
	t_ints		num;
	t_rlines	var;

	var = ft_rlines_dup(data->var);
	num.len = ft_rlines_len(var);
	while (--num.len >= 0)
	{
		max = "\0";
		num = (t_ints){.count = num.len + 1, .j = num.len, .len = num.len};
		while (--num.count >= 0)
		{
			if (is_greater(var[num.count], max))
			{
				max = var[num.count];
				num.i = num.count;
			}
		}
		max = var[num.i];
		var[num.i] = var[num.j];
		var[num.j] = max;
	}
	ft_print_var(var);
	ft_free_rlines(&var);
	return (0);
}

int	is_greater(char *s1, char *s2)
{
	int	index;

	index = 0;
	while (s1[index] && s1[index] == s2[index])
		index++;
	if (s1[index] > s2[index])
		return (1);
	return (0);
}
