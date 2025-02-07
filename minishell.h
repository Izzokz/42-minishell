/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:20:53 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/07 14:30:41 by pboucher         ###   ########.fr       */
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

# define MINI "\e[1;34m[\e[1;31mm\e[1;32mi\e[1;33mn\e[1;34mi\e[1;35mPK\e[1;34m]"
# define USER "\e[1;33m@"
# define PBEG " \e[1;35m{"
# define PEND "} \e[1;31m»\e[0;97m "

# define ERRORCD "\e[1;31m[Minishell] \e[0;97mNo such file or directory\e[0m\n"

struct	s_pipeline;

typedef struct s_data
{
	char				*user;
	char				*line;
	char				**path;
	int					pid;
	int					pipe[2];
	int					swap_pipe;
	int					fd;
	int					exe;
	t_rlines			envp;
	t_slines			input;
	struct s_pipeline	*pipeline;
	struct sigaction	usr;
}	t_data;

typedef struct s_pipeline
{
	int		(*func)(t_data *, void *);
	void	(*free)();
	void	*param;
	void	*next;
}	t_pipeline;

//	000_MAIN
//->	001_SPLIT_PARSING
	/*	ft_split_redirec.c */
int			ft_split_redirec(t_rlines *part, int j);
	/*	ft_fix_redirections.c */
int			ft_fix_redirections(t_slines *input);
	/*	ft_pipe_split.c */
t_slines	ft_pipe_split(char *line, t_rlines envp);
	/*	ft_remove_quotes.c */
int			ft_remove_quotes(t_slines input);
	/*	ft_fix_order.c */
int			ft_fix_order(t_slines *input);
//->	002_PIPELINE
	/*	ft_loop.c */
int			ft_loop(t_data *data);
	/*	ft_exec.c */
int			ft_exec(t_data *data, t_rlines cmd);
	/*	ft_make_pipeline.c */
int			ft_make_pipeline(t_data *data);
	/*	ft_pipeline_function_set.c */
t_pipeline	*ft_new_pipeline(int (*func)(t_data *, void *),
				void *param, void (*free)());
void		ft_destroy_pipeline(t_pipeline *start);
int			ft_add_pipeline(t_pipeline *prev, int (*func)(t_data *, void *),
				void *param, void (*free)());

//	100_UTILS
/*	ft_free_all.c */
void		ft_free_all(t_data *data);
/*	ft_free_tab.c */
void		ft_free_tab(t_rlines *rlines);
/*	ft_path.c */
void		ft_set_path(t_data *data);
char		*ft_get_path(char *filename, char **all_path);
/*	ft_expand.c */
int			ft_expand_line(char **input, t_rlines envp);
/*	ft_expand_rlines.c */
int			ft_expand_rlines(t_rlines *rlines, t_rlines envp);
int			ft_expand_slines(t_slines *slines, t_rlines envp);

//	110_BUILTINS
/*	ft_exit.c */
void		ft_exit(t_data *data, t_rlines cmd);
/*	ft_cd.c */
int			ft_cd(t_data *data, t_rlines cmd);
/*	ft_pwd.c */
int			ft_pwd(t_data *data, t_rlines cmd);
/*	ft_unset.c */
int			ft_unset(t_data *data, t_rlines cmd);
/*	ft_echo.c */
int			ft_echo(t_rlines cmd);
/*	ft_export.c */
int			ft_export(t_data *data, t_rlines cmd);

#endif
