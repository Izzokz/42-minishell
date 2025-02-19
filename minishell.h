/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:20:53 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/19 15:41:25 by pboucher         ###   ########.fr       */
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
# include <termios.h>

# define MI "\1\e[1;34m[\e[1;31mm\e[1;32mi"
# define NI "\e[1;33mn\e[1;34mi\e[1;35mPK\e[1;34m]"
# define USER "\e[1;33m@"
# define SHLVL " \e[1;32m[Lv. "
# define PBEG " \e[1;35m{"
# define PEND "} \e[1;31m»\e[0;97m \2"

# define ERRORCD "\e[1;31m[Minishell] \e[0;97mNo such file or directory\e[0m\n"

struct	s_pipeline;

typedef struct s_data
{
	char				*user;
	char				*line;
	char				**path;
	char				*history;
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
	/*	ft_history.c */
void		ft_gen_history(t_data *data);
void		ft_add_history(t_data *data);
//->	001_SPLIT_PARSING
	/*	ft_split_redirec.c */
int			ft_split_redirec(t_rlines *part, int j);
	/*	ft_fix_redirections.c */
int			ft_fix_redirections(t_slines *input);
	/*	ft_pipe_split.c */
t_slines	ft_pipe_split(char *line);
	/*	ft_fix_order.c */
int			ft_fix_order(t_slines *input);
	/*	ft_valid_input.c */
int			ft_valid_input(char *input);
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
/*	ft_path.c */
void		ft_set_path(t_data *data);
char		*ft_get_path(char *filename, char **all_path);
/*	ft_expand_split.c */
void		split_space(char ***line, char **var, t_ints *info);
/*	ft_expand_remap.c */
int			remap(char ***line, t_ints *i);
/*	ft_expand_slines.c */
int			ft_expand_line(char **input, t_ints *info);
int			ft_expand_slines(t_slines *slines);
/*	ft_tdata.c */
void		ft_set_tdata(t_data *info);
t_data		*ft_get_tdata(void);
/*	ft_is_env.c */
char		*ft_pick_env(char *var);
int			ft_is_env(char *var);

//	110_BUILTINS
/*	ft_exit.c */
void		ft_exit(t_data *data, t_rlines cmd);
/*	ft_cd.c */
int			ft_cd(t_data *data, t_rlines cmd);
/*	ft_pwd.c */
int			ft_pwd(void);
/*	ft_unset.c */
int			ft_unset(t_data *data, t_rlines cmd);
/*	ft_echo.c */
int			ft_echo(t_rlines cmd);
/*	ft_export.c */
int			ft_export(t_data *data, t_rlines cmd);

#endif
