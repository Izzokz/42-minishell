/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:30:08 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/19 14:46:06 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_chr(char *cmd)
{
	t_ints	i;

	if (ft_isdigit(cmd[0]))
		return (0);
	i.i = -1;
	while (cmd[++(i.i)])
		if (cmd[i.i] == '=')
			return (i.i);
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

static int	ft_print_export(t_data *data)
{
	char		*max;
	t_ints		num;
	t_rlines	envp;

	envp = ft_rlines_dup(data->envp);
	num.len = ft_rlines_len(envp);
	while (--num.len >= 0)
	{
		max = "\0";
		num = (t_ints){.count = num.len + 1, .j = num.len, .len = num.len};
		while (--num.count >= 0)
		{
			if (is_greater(envp[num.count], max))
			{
				max = envp[num.count];
				num.i = num.count;
			}
		}
		max = envp[num.i];
		envp[num.i] = envp[num.j];
		envp[num.j] = max;
	}
	ft_printf("declare -x %*[\ndeclare -x ]s\n", envp);
	ft_free_rlines(&envp);
	return (0);
}

int	ft_export(t_data *data, t_rlines cmd)
{
	t_ints	ints;
	char	*dup;

	(void)data;
	ints.len = ft_rlines_len(cmd);
	if (ints.len == 1)
		return (ft_print_export(data));
	ints.i = 0;
	while (cmd[++(ints.i)])
	{
		ints.j = ft_chr(cmd[ints.i]);
		if (ints.j)
		{
			dup = ft_substr(cmd[ints.i], 0, ints.j + 1);
			if (!dup)
				return (ft_printf_err("Internal Error:ft_substr(%*.)", 2));
			ft_make_export(data, cmd, &ints, dup);
		}
		else
			ft_printf_fd("\e[1;31m[Minishell] \e[0;97m%s\e[0m\n", 2,
				"not a valid identifier");
	}
	return (0);
}
