/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:07:10 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/03/14 14:48:23 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_line(t_data *data)
{
	free(data->line);
	data->line = NULL;
	return (1);
}

void	ft_free_tab(t_rlines rlines)
{
	ft_free_rlines(&rlines);
}

void	ft_free_all(t_data *data)
{
	ft_free_rlines(&data->envp);
	ft_free_rlines(&data->var);
	ft_free_slines(&data->input);
	ft_free_rlines(&data->path);
	ft_free_rlines(&data->rcases);
	ft_free_rlines(&data->temp_history);
	ft_destroy_all_pipelines(&(data->pipeline));
	free(data->line);
	free(data->user);
	free(data->history);
	if (data->last_history)
		free(data->last_history);
	if (data->input_fd >= 0)
		close(data->input_fd);
	if (data->output_fd >= 0)
		close(data->output_fd);
	if (data->pipe[0] >= 0)
		close(data->pipe[0]);
	if (data->pipe[1] >= 0)
		close(data->pipe[1]);
	if (data->prevpipe >= 0)
		close(data->prevpipe);
	rl_clear_history();
}
