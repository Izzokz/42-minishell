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

static int	hd_free(t_rlines *buffer, char *line, int is_add_func)
{
	free(line);
	ft_free_rlines(buffer);
	if (is_add_func)
		ft_printf_err("Internal Error:ft_rlines_add(%*.)", 2);
	return (-1);
}

static int	is_lim_reached(char *lim, char *line)
{
	int	len;

	len = ft_strlen(lim);
	if (lim[0] == '\'' || lim[0] == '"')
	{
		len = ft_strlen(lim);
		return (!ft_strncmp(lim + 1, line, len - 2));
	}
	return (!gnlxio_ft_strcmp(lim, line));
}

int	ft_here_doc(t_data *data, char *lim)
{
	char		*line;
	t_rlines	buffer;
	t_ints		i;

	if (data->input_fd >= 0)
		close(data->input_fd);
	if (ft_gen_file("..!minipk_hd42", "0744") == -1)
		return (ft_printf_err("Internal Error:ft_gen_file(%*.)", 2));
	buffer = ft_calloc(1, sizeof(char *));
	while (1)
	{
		line = readline("> ");
		if (!line || is_lim_reached(lim, line))
			break ;
		i = (t_ints){.height = -42, .tmp1 = -42, .i = -1};
		if ((lim[0] == '\'' || lim[0] == '"')
			&& ft_expand_line(&line, &i) == -1)
			return (hd_free(&buffer, line, 0));
		if (ft_rlines_add(&buffer, line, A_END) == -1)
			return (hd_free(&buffer, line, 1));
	}
	ft_rewrite_file("..!minipk_hd42", buffer);
	ft_free_rlines(&buffer);
	data->input_fd = open("..!minipk_hd42", O_RDONLY);
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
