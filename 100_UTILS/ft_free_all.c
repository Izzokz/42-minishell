/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:07:10 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/02/13 15:02:34 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all(t_data *data)
{
	ft_free_rlines(&data->envp);
	ft_free_slines(&data->input);
	ft_free_rlines(&data->path);
	if (data->pipeline)
		ft_destroy_all_pipelines(data->pipeline);
	free(data->line);
	free(data->user);
	free(data->history);
	if (data->input_fd >= 0)
		close(data->input_fd);
	if (data->output_fd >= 0)
		close(data->output_fd);
}
