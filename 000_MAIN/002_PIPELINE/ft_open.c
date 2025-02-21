/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:04:14 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/02/20 12:04:15 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_here_doc(t_data *data, char *filename)
{
	if (data->input_fd >= 0)
		close(data->input_fd);
	data->input_fd = ;
}

int	ft_open_read(t_data *data, char *filename)
{
	if (data->input_fd >= 0)
		close(data->input_fd);
	data->input_fd = open(filename, O_RDONLY);
}

int	ft_open_trunc(t_data *data, char *filename)
{
	if (data->output_fd >= 0)
		close(data->output_fd);
	data->output_fd = open(filename, O_WRONLY | O_TRUNC);
}

int	ft_open_append(t_data *data, char *filename)
{
	if (data->output_fd >= 0)
		close(data->output_fd);
	data->output_fd = open(filename, O_WRONLY | O_APPEND);
}
