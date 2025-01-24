/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:20:53 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/24 15:35:24 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "010_FT_PRINTF/ft_printf.h"
# include "020_LIBFT/libft.h"
# include <signal.h>
# include <sys/wait.h>

typedef struct s_data
{
	char				*line;
	char				**path;
	int					pid;
	int					*pipe;
	int					swap_pipe;
	int					fd;
	int					exe;
	t_rlines			envp;
	t_slines			input;
	t_slines			pipeline;
	struct sigaction	usr;
}	t_data;

//	000_MAIN
/*	ft_exec.c */
int			ft_exec(t_data *data, t_rlines cmd);
/*	ft_make_pipeline.c */
int			ft_make_pipeline(t_data *data);
/*	ft_parsing.c */
/*	ft_pipe_split.c */
t_slines	ft_pipe_split(char *line);

//	100_UTILS
/*	ft_free_all.c */
void		ft_free_all(t_data *data);
/*	ft_path.c */
void		ft_set_path(t_data *data);
char		*ft_get_path(char *filename, char **all_path);

//	110_BUILTINS
/*	ft_exit.c */
void		ft_exit(t_data *data, t_rlines cmd);


#endif
