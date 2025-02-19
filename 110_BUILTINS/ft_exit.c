/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:50:34 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/01/24 13:55:42 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static void	did_overflow(long number, int *err)
{
	static long	n;
	static int	init = 0;

	if (!err)
	{
		init = 0;
		return ;
	}
	if (!init)
	{
		n = number;
		init = 1;
	}
	else
	{
		if (n > number)
			*err = 1;
		else
			n = number;
	}
}

static long	ft_atol(const char *str, int *err)
{
	long	number;
	int		index;
	int		sign;

	number = 0;
	index = -1;
	sign = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		index++;
		if (str[0] == '-')
			sign = -1;
	}
	while (str[++index] && !(*err))
	{
		if (ft_isdigit(str[index]))
			number = number * 10 + str[index] - '0';
		else
			*err = 1;
		did_overflow(number, err);
	}
	did_overflow(0, NULL);
	if (!(*err) && index == 1 && (str[0] == '-' || str[0] == '+'))
		*err = 1;
	return (number * sign);
}

static int	numerical(char *str, long *i)
{
	int	err;

	err = 0;
	if (!ft_strncmp(str, "-9223372036854775808", -1))
		*i = LONG_MIN;
	else
		*i = ft_atol(str, &err);
	return (!err);
}

void	ft_exit(t_data *data, t_rlines cmd)
{
	int		len;
	long	exit_id;

	len = ft_rlines_len(cmd);
	if (len > 1 && !numerical(cmd[1], &exit_id))
	{
		ft_printf_fd("\e[1;31m[Minishell] \e[0;97m%s: not valid\e[0m\n",
			2, cmd[1]);
		errno = 2;
	}
	else if (len > 2)
	{
		ft_printf_fd("\e[1;31m[Minishell] \e[0;97mtoo many args\e[0m\n", 2);
		errno = 1;
		if (ft_slines_rlen(data->input) == 1)
			return ;
	}
	else if (len == 2)
		errno = (char)exit_id;
	if (!data->input || ft_slines_rlen(data->input) == 1)
		ft_printf("exit\n");
	ft_free_all(data);
	exit(errno);
}
