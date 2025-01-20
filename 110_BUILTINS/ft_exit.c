/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:50:34 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/01/20 14:50:35 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_data *data)
{
	ft_free_all(data);
	exit(errno);
}

void	ft_exit_id(t_data *data, int exit_id)
{
	ft_free_all(data);
	exit((char)exit_id);
}
