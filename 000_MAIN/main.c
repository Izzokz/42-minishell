/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:23:35 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/08 16:44:30 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int n)
{
	if (n == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	print_slines_test(t_slines slines)
{
	int	i;

	if (!slines)
		return ((void)ft_printf("No slines\n"));
	i = -1;
	while (slines[++i])
	{
		ft_printf("%*[ ]s", slines[i]);
		ft_printf("\n");
	}
}

static void	ft_get_user(t_data *data)
{
	t_ints	num;

	num.i = -1;
	while (data->envp && data->envp[++(num.i)])
		if (!ft_strncmp(data->envp[num.i], "USER=", 5))
			break ;
	if (!data->envp || !data->envp[num.i])
		data->user = ft_strdup("user");
	else
		data->user = ft_substr(data->envp[num.i], 5, -1);
}

static int	is_env_var(char *var, char **envp)
{
	char	*lim;
	int		i;

	lim = ft_strjoin(var, "=");
	if (!lim)
		return (ft_printf_err("Internal Error:ft_strjoin(%*.)", 2) + 1);
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], lim, 5))
		{
			free(lim);
			return (1);
		}
	}
	free(lim);
	return (0);
}

static int	set_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->pipeline = NULL;
	data->line = NULL;
	data->envp = NULL;
	data->path = NULL;
	data->envp = ft_rlines_dup(envp);
	if (!invalid_rlines(envp) && invalid_rlines(data->envp))
		return (ft_printf_err("Internal Error:ft_rlines_dup(%*.)", 2));
	ft_get_user(data);
	if (!data->user)
		ft_printf_err("Internal Error:ft_get_user()", 2);
	ft_set_path(data);
	if (is_env_var("PATH", data->envp) && invalid_rlines(data->path))
	{
		ft_free_all(data);
		return (ft_printf_err("Internal Error:ft_set_path(%*.)", 2));
	}
	return (0);
}

static char	*ft_generate_path(t_data *data)
{
	char	*path;
	char	*prompt;
	char	*tmp;
	int		i;

	tmp = getcwd(NULL, 0);
	if (!tmp)
	{
		ft_printf_err("Internal Error:getcwd(%*.)", 2);
		return (NULL);
	}
	i = ft_strlen(tmp) - 1;
	while (tmp[i] != '/')
		i--;
	path = ft_substr(tmp, i + 1, -1);
	if (path[0] == 0)
		path = gnlxio_ft_strjoinfree(&path, &(char *){ft_strdup("/")});
	free(tmp);
	prompt = gnlxio_ft_strjoinfree(&(char *){ft_strdup(MINI)},
			&(char *){ft_strdup(USER)});
	prompt = gnlxio_ft_strjoinfree(&prompt, &(char *){ft_strdup(data->user)});
	prompt = gnlxio_ft_strjoinfree(&prompt, &(char *){ft_strdup(PBEG)});
	prompt = gnlxio_ft_strjoinfree(&prompt, &path);
	prompt = gnlxio_ft_strjoinfree(&prompt, &(char *){ft_strdup(PEND)});
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
		num.j = 0;
	free(data->envp[num.i]);
	free(temp);
	data->envp[num.i] = gnlxio_ft_strjoinfree(&str, &(char *){ft_itoa(num.j)});
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*prompt;

	(void) argc;
	(void) argv;
	if (set_data(&data, envp) == -1)
		return (-1);
	up_shlvl(&data);
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		prompt = ft_generate_path(&data);
		data.line = readline(prompt);
		free(prompt);
		if (!data.line)
			break ;
		if (data.line[0])
		{
			data.input = ft_pipe_split(data.line, data.envp);
			print_slines_test(data.input);
			free(data.line);
			data.line = NULL;
			//data.pipeline = ft_make_pipeline(&data);
			//ft_printf("%*.2[\n]s\n", data.input); //just testing the parsing.
			if (!data.input) // if exit in the pipeline, frees input and returns instantly.
				break ;
			ft_loop(&data);
			ft_free_slines(&data.input);
		}
		free(data.line);
		data.line = NULL;
	}
	ft_free_all(&data);
	ft_printf("exit\n");
	return (0);
}
