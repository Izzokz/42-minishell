/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:52:47 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/06 17:29:02 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_realloc(char **buffer, unsigned int ext)
{
	char	*temp_buffer;

	if (!ext || !(*buffer))
		return ;
	temp_buffer = ft_strdup(*buffer);
	if (!temp_buffer)
		return ;
	free(*buffer);
	*buffer = ft_calloc(ft_strlen(temp_buffer) + ext + 1, sizeof(char));
	if (!(*buffer))
	{
		free(temp_buffer);
		return ;
	}
	ft_strlcat(*buffer, temp_buffer, -1);
	free(temp_buffer);
}

void	ft_set_path(t_data *data)
{
	char	*path_line;
	int		i;

	data->path = NULL;
	i = -1;
	while (data->envp[++i])
	{
		if (ft_strnstr(data->envp[i], "PATH=", 5))
		{
			path_line = ft_substr(data->envp[i], 5, -1);
			if (!path_line)
				return ;
			data->path = ft_split(path_line, ':');
			free(path_line);
			i = -1;
			while (data->path && data->path[++i])
			{
				ft_realloc(&(data->path[i]), 1);
				ft_strlcat(data->path[i], "/", -1);
			}
			if (data->path)
				ft_realloc(data->path, 1);
			return ;
		}
	}
}

char	*ft_get_path(char *file, char **all_path)
{
	int		i;
	char	*path;

	if (!ft_strncmp(file, "exit", -1))
		return (ft_strdup(file));
	if (file[0] == '/' || file[0] == '.')
		if (access(file, X_OK) != -1)
			return (ft_strdup(file));
	i = -1;
	if (all_path)
	{
		while (all_path[++i])
		{
			path = ft_strjoin(all_path[i], file);
			if (!path)
				return (NULL);
			if (access(path, X_OK) != -1)
				return (path);
			free(path);
		}
	}
	ft_printf_fd("\e[1;31m[Minishell] \e[0;97m%s: not found\e[0m\n", 2, file);
	return (NULL);
}
