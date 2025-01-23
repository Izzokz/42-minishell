/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:07:10 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/01/16 13:07:12 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_all(t_data *data)
{
	ft_free_rlines(&data->envp);
	ft_free_slines(&data->input);
	ft_free_rlines(&data->path);
	free(data->line);
}
