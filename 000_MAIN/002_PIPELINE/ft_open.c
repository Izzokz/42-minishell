/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:04:14 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/02/28 18:51:02 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_read(t_data *data, void *filename)
{
	if (data->input_fd >= 0)
		close(data->input_fd);
	data->input_fd = open((char *)filename, O_RDONLY);
	if (data->input_fd == -1)
		ft_printf_fd(ERROR_FDE, 2, filename);
	return (data->input_fd);
}

int	ft_open_trunc(t_data *data, void *filename)
{
	if (data->output_fd >= 0)
		close(data->output_fd);
	data->output_fd = open((char *)filename,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (data->output_fd == -1)
		ft_printf_fd(ERROR_FDE, 2, filename);
	return (data->output_fd);
}

int	ft_open_append(t_data *data, void *filename)
{
	if (data->output_fd >= 0)
		close(data->output_fd);
	data->output_fd = open((char *)filename,
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (data->output_fd == -1)
		ft_printf_fd(ERROR_FDE, 2, filename);
	return (data->output_fd);
}
