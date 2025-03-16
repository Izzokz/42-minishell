/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:55:33 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/15 21:07:08 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_data(t_data *data, char **envp)
{
	*data = (t_data){.input_fd = -42, .output_fd = -42, .input = NULL,
		.pipeline = NULL, .line = NULL, .path = NULL, .pipe = {-1, -1},
		.prevpipe = -1, .endpipe = 0, .history = NULL, .user = NULL,
		.envp = ft_rlines_dup(envp), .var = ft_rlines_dup(envp)};
	if (!invalid_rlines(envp) && invalid_rlines(data->envp))
		return (ft_printf_err(ERROR_IE"ft_rlines_dup(%*.)", 2));
	ft_get_user(data);
	if (!data->user)
		ft_printf_err(ERROR_IE"ft_get_user()", 2);
	ft_set_path(data);
	if (is_env_var("PATH", data->envp) && invalid_rlines(data->path))
	{
		ft_free_all(data);
		return (ft_printf_err(ERROR_IE"ft_set_path(%*.)", 2));
	}
	return (0);
}

char	*ft_generate_prompt(t_data *data, char *path)
{
	char	*prompt;
	char	*shlvl;

	shlvl = ft_pick_env("SHLVL");
	if (!shlvl)
		shlvl = ft_strdup("UNK");
	prompt = gnlxio_ft_strjoinfree(&(char *){ft_strdup(MI)},
			&(char *){ft_strdup(NI)});
	prompt = gnlxio_ft_strjoinfree(&prompt, &(char *){ft_strdup(USER)});
	prompt = gnlxio_ft_strjoinfree(&prompt, &(char *){ft_strdup(data->user)});
	if (shlvl)
	{
		prompt = gnlxio_ft_strjoinfree(&prompt, &(char *){ft_strdup(SHLVL)});
		prompt = gnlxio_ft_strjoinfree(&prompt, &shlvl);
		prompt = gnlxio_ft_strjoinfree(&prompt, &(char *){ft_strdup("]")});
	}
	prompt = gnlxio_ft_strjoinfree(&prompt, &(char *){ft_strdup(PBEG)});
	prompt = gnlxio_ft_strjoinfree(&prompt, &path);
	prompt = gnlxio_ft_strjoinfree(&prompt, &(char *){ft_strdup(PEND)});
	return (prompt);
}

char	*ft_generate_path(t_data *data)
{
	char	*path;
	char	*prompt;
	char	*tmp;
	int		i;

	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		ft_printf_err(ERROR_IE"getcwd(%*.)", 2);
		return (NULL);
	}
	i = ft_strlen(tmp) - 1;
	while (tmp[i] != '/')
		i--;
	path = ft_substr(tmp, i + 1, -1);
	if (path[0] == 0)
		path = gnlxio_ft_strjoinfree(&path, &(char *){ft_strdup("/")});
	free(tmp);
	prompt = ft_generate_prompt(data, path);
	return (prompt);
}

void	up_shlvl(t_data *data)
{
	t_ints	num;
	char	*temp;
	char	*str;

	num.i = -1;
	num.j = 0;
	while (data->envp && data->envp[++(num.i)])
		if (!ft_strncmp(data->envp[num.i], "SHLVL=", 6))
			break ;
	if (!data->envp || !data->envp[num.i])
		return ;
	temp = ft_substr(data->envp[num.i], 6, -1);
	str = ft_substr(data->envp[num.i], 0, 6);
	num.j = ft_atoi(temp);
	num.j++;
	if (num.j >= 1000)
		num.j = 1;
	free(data->envp[num.i]);
	free(temp);
	data->envp[num.i] = gnlxio_ft_strjoinfree(&str, &(char *){ft_itoa(num.j)});
}

void	ft_show_prompt(t_data *data)
{
	char	*prompt;

	prompt = ft_generate_path(data);
	data->line = readline(prompt);
	free(prompt);
}
