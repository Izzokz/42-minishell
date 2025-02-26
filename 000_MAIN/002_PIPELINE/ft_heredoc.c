/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:49:23 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/02/26 15:50:20 by pboucher         ###   ########.fr       */
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

static int	is_lim_reached(char *lim, char **line)
{
	int	len;

	len = ft_strlen(lim);
	if (lim[0] == '\'' || lim[0] == '"')
	{
		len = ft_strlen(lim);
		if (!ft_strncmp(lim + 1, *line, len - 2))
		{
			free(*line);
			return (1);
		}
		return (0);
	}
	if (!gnlxio_ft_strcmp(lim, *line))
	{
		free(*line);
		return (1);
	}
	return (0);
}

int	ft_here_doc(t_data *data, void *lim)
{
	char		*line;
	t_rlines	buffer;
	t_ints		i;

	if (ft_gen_file("..!minipk_hd42", "0744") == -1)
		return (ft_printf_err("Internal Error:ft_gen_file(%*.)", 2));
	buffer = ft_calloc(1, sizeof(char *));
	while (1)
	{
		line = readline("miniHD > ");
		if (!line || is_lim_reached((char *)lim, &line))
			break ;
		i = (t_ints){.height = -42, .tmp1 = -42, .i = -1};
		if ((((char *)lim)[0] != '\'' && ((char *)lim)[0] != '"')
			&& ft_expand_line(&line, &i) == -1)
			return (hd_free(&buffer, line, 0));
		if (ft_rlines_add(&buffer, line, A_END) == -1)
			return (hd_free(&buffer, line, 1));
	}
	ft_rewrite_file("..!minipk_hd42",
		buffer + (ft_rlines_addendl(&buffer) * 0));
	ft_free_rlines(&buffer);
	data->input_fd = open("..!minipk_hd42", O_RDONLY);
	return (0);
}
