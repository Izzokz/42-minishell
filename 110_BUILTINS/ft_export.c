/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:30:08 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/04 16:20:37 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_chr(char *cmd)
{
	int	i;

	if (ft_isdigit(cmd[0]))
		return (-1);
	i = -1;
	while (cmd[++(i)])
	{
		if (cmd[i] == '+' && cmd[i + 1] != '=')
			return (-1);
		if (cmd[i] == '=')
			return (i);
	}
	return (0);
}

static void	ft_make_export(t_data *data, t_rlines cmd, t_ints *ints, char *dup)
{
	ints->k = -1;
	ints->count = 0;
	while (data->envp[++ints->k])
	{
		ints->count1 = ft_strncmp(data->envp[ints->k], dup, ft_strlen(dup));
		if (!ints->count1)
		{
			ints->count++;
			break ;
		}
	}
	if (ints->count)
	{
		free(dup);
		free(data->envp[ints->k]);
		data->envp[ints->k] = ft_strdup(cmd[ints->i]);
	}
	else
	{
		free(dup);
		dup = ft_strdup(cmd[ints->i]);
		ft_rlines_add(&(data->envp), dup, A_END);
	}
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

static int	ft_execute(t_data *data, t_rlines cmd, t_ints *ints)
{
	char	*dup;

	if (ints->j >= 0)
	{
		dup = ft_substr(cmd[ints->i], 0, ints->j + 1);
		if (!dup)
			return (ft_printf_err("Internal Error:ft_substr(%*.)", 2));
		ft_make_export(data, cmd, ints, dup);
		dup = ft_substr(cmd[ints->i], 0, ints->j);
		if (!dup)
			return (ft_printf_err("Internal Error:ft_substr(%*.)", 2));
		ft_make_var(data, cmd, ints, dup);
	}
	else if (ints->j == 0)
	{
		dup = ft_substr(cmd[ints->i], 0, -1);
		if (!dup)
			return (ft_printf_err("Internal Error:ft_substr(%*.)", 2));
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
