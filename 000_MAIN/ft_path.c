/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:52:47 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/23 15:03:11 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			while (data->path[++i])
			{
				ft_realloc(&(data->path[i]), 1);
				ft_strlcat(data->path[i], "/", -1);
			}
			ft_realloc(data->path, 1);
			return ;
		}
	}
	return ;
}

char	*ft_get_path(char *filename, char **all_path)
{
	int		i;
	char	*path;

	path = NULL;
	i = -1;
	if (!all_path)
		return (NULL);
	if (filename[0] == '/')
		if (access(filename, X_OK) != -1)
			return (ft_strdup(filename));
	while (all_path[++i])
	{
		path = ft_strjoin(all_path[i], filename);
		if (!path)
			return (NULL);
		if (access(path, X_OK) != -1)
			return (path);
		free(path);
	}
	if (ft_strlen(filename) > 1 && filename[0] == '.' && filename[1] == '/'
		&& access(filename, X_OK) != -1)
		return (get_in_dir(filename));
	ft_printf("Pipex:%s(access=%_1)\n", filename, 0);
	return (NULL);
}