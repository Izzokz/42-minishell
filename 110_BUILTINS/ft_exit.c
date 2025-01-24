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

#include "../minishell.h"

static int	numerical(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

void	ft_exit(t_data *data, t_rlines cmd)
{
	int	len;

	len = ft_rlines_len(cmd);
	if (len > 1 && !numerical(cmd[1]))
		errno = 2;
	else if (len > 2)
		errno = 1;
	else if (len == 2 && numerical(cmd[1]))
		errno = (char)ft_atoi(cmd[1]);
	ft_free_all(data);
	exit(errno);
}
