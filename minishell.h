/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:20:53 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/22 15:03:01 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "010_FT_PRINTF/ft_printf.h"
# include <signal.h>

typedef struct s_data
{
	char				*line;
	char				**path;
	int					id1;
	int					id2;
	t_rlines			envp;
	t_slines			input;
	t_slines			pipeline;
	struct sigaction	usr;
}	t_data;

t_slines	ft_pipe_split(char *line);
void		ft_exit_id(t_data *data, int exit_id);
void		ft_exit(t_data *data);
int			ft_make_pipeline(t_data *data);
void		ft_free_all(t_data *data);

#endif
