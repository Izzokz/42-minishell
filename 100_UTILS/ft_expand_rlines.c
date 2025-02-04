/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_rlines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:59:20 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/02/04 11:59:21 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expand_rlines(t_rlines *input, t_rlines envp)
{
	int	i;

	i = -1;
	while ((*input)[++i])
		if (ft_expand_line(&((*input)[i]), envp) == -1)
			return (-1);
	return (0);
}

int	ft_expand_slines(t_slines *input, t_rlines envp)
{
	int	i;

	i = -1;
	while ((*input)[++i])
		if (ft_expand_rlines(&((*input)[i]), envp) == -1)
			return (-1);
	return (0);
}
