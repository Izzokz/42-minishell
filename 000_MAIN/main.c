/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:23:35 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/16 12:13:14 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_user(t_data *data)
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

static int	finish(t_data *data)
{
	ft_add_all_history(data);
	ft_exit(data, NULL);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (ft_init(argc, argv, envp, &data) == -1)
		return (-1);
	while (1)
	{
		ft_show_prompt(&data);
		if (!data.line)
			break ;
		ft_add_history(&data);
		if (!ft_valid_input(data.line) && ft_free_line(&data))
			continue ;
		if (data.line[0])
		{
			data.input = ft_pipe_split(data.line);
			ft_free_line(&data);
			if (!data.input || ft_make_pipeline(&data) == -1)
				break ;
			ft_hd_loop(&data);
			ft_destroy_all_pipelines(&(data.pipeline));
			ft_free_slines(&data.input);
		}
		ft_free_line(&data);
	}
	return (finish(&data));
}
