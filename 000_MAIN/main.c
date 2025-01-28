/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:23:35 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/28 14:45:43 by pboucher         ###   ########.fr       */
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
		ft_printf("%*[:]s", slines[i]);
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

int    main(int argc, char **argv, char **envp)
{
    t_data data;
    char    *path;

    (void) argc;
    (void) argv;
    if (set_data(&data, envp) == -1)
        return (-1);
    while (1)
    {
        signal(SIGINT, handler);
        signal(SIGQUIT, SIG_IGN);
        path = gnlxio_ft_strjoinfree(&(char *){getcwd(NULL, 0)},
                    &(char *){ft_strdup("\e[1;34m/Minishell » \e[0;97m")});
        path = gnlxio_ft_strjoinfree(&(char *){ft_strdup("\e[1;33m")},
                    &path);
        data.line = readline(path);
        free(path);
        if (!data.line)
            break ;
        if (data.line[0])
        {
            data.input = ft_pipe_split(data.line);
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
