/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:30:08 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/06 19:43:58 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_chr(char *cmd)
{
	t_ints	i;

	i.i = -1;
	while (cmd[++(i.i)])
		if (cmd[i.i] == '=' && !ft_isdigit(cmd[0]))
			return (i.i);
	return (0);
}

static void	ft_replace_data(t_data *data, t_ints ints, char *old)
{
	free(data->envp[ints.k]);

	data->envp[ints.k] = ft_strdup(old);
}

int	ft_export(t_data *data, t_rlines cmd)
{
	t_ints	ints;
	char	*dup;

	(void)data;
	ints.len = ft_rlines_len(cmd);
	if (ints.len == 1)
		return (ft_printf_fd("\e[1;31m[Minishell] \e[0;97m%s\e[0m\n", 2,
				"not enough arguments"));
	ints.i = 0;
	while (cmd[++(ints.i)])
	{
		ints.j = ft_chr(cmd[ints.i]);
		if (ints.j)
		{
			dup = ft_substr(cmd[ints.i], 0, ints.j + 1);
			if (!dup)
				return (ft_printf_err("Internal Error:ft_substr(%*.)", 2));
			ints.k = -1;
			ints.count = 0;
			while (data->envp[++ints.k])
				if (!ft_strncmp(data->envp[ints.k], dup, ft_strlen(dup)))
				{
					ints.count++;
					break;
				}
			if (ints.count)
			{
				free(dup);
				ft_replace_data(data, ints, cmd[ints.i]);
			}
			else
			{
				free(dup);
				dup = ft_strdup(cmd[ints.i]);
				ft_rlines_add(&(data->envp), dup, A_END);
				free(dup);
			}
		}
		else
			ft_printf_fd("\e[1;31m[Minishell] \e[0;97m%s\e[0m\n", 2,
				"not a valid identifier");
	}
	return (0);
}
