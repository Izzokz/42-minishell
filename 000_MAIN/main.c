/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:23:35 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/04 15:31:10 by pboucher         ###   ########.fr       */
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

static int	set_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->pipeline = NULL;
	data->line = NULL;
	data->envp = NULL;
	data->path = NULL;
	data->envp = ft_rlines_dup(envp);
	if (!data->envp)
		return (ft_printf_err("Internal Error:ft_rlines_dup(%*.)", 2));
	ft_set_path(data);
	if (!data->path)
	{
		ft_free_all(data);
		return (ft_printf_err("Internal Error:ft_set_path(%*.)", 2));
	}
	return (0);
}

static char	*ft_generate_path(void)
{
	char	*path;
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
	free(tmp);
	path = gnlxio_ft_strjoinfree(&(char *){ft_strdup(PROMPT)}, &path);
	path = gnlxio_ft_strjoinfree(&path, &(char *){ft_strdup(LOCAL)});
	return (path);
}

void	up_shlvl(t_data *data)
{
	t_ints	num;
	char	*temp;
	char	*str;
	
	num.i = 0;
	num.j = 0;
	while (data->envp[num.i])
	{
		if (!ft_strncmp(data->envp[num.i], "SHLVL=", 6))
			break;
		num.i++;
	}
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
	char	*path;

	(void) argc;
	(void) argv;
	if (set_data(&data, envp) == -1)
		return (-1);
	up_shlvl(&data);
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		path = ft_generate_path();
		data.line = readline(path);
		free(path);
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
