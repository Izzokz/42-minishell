/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:21:15 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/01/27 19:21:17 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_remove_quotes(t_slines input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (ft_replace_rlines(&input[i], "'", NULL) == -1)
			return (-1);
		if (ft_replace_rlines(&input[i], "\"", NULL) == -1)
			return (-1);
	}
	return (0);
}
