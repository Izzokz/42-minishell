/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:20:53 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/24 14:06:22 by pboucher         ###   ########.fr       */
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

# define MI "\1\e[1;34m\2[\1\e[1;31m\2m\1\e[1;32m\2i"
# define NI "\1\e[1;33m\2n\1\e[1;34m\2i\1\e[1;35m\2PK\1\e[1;34m]\2"
# define USER "\1\e[1;33m\2@"
# define SHLVL " \1\e[1;32m\2[Lv. "
# define PBEG " \1\e[1;35m\2{"
# define PEND "} \1\e[1;31m\2»\1\e[0;97m\2 "

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
	int					prevpipe;
	int					endpipe;
	int					input_fd;
	int					output_fd;
	int					fd;
	int					exe;
	t_rlines			envp;
	t_rlines			var;
	t_slines			input;
	struct s_pipeline	**pipeline;
	struct sigaction	usr;
}	t_data;

typedef struct s_pipeline
{
	int		(*func)(t_data *, void *);
	void	*param;
	void	(*free)();
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
//int			ft_loop(t_data *data);
	/*	ft_exec.c */
//int			ft_exec(t_data *data, t_rlines cmd);
	/*	ft_loop_tmp.c */
int			ft_loop(t_data *data);
	/*	ft_exec_tmp.c */
int			ft_exec(t_data *data, void *cmd);
	/*	ft_heredoc.c */
int			ft_here_doc(t_data *data, void *lim);
	/*	ft_open.c */
int			ft_open_read(t_data *data, void *filename);
int			ft_open_trunc(t_data *data, void *filename);
int			ft_open_append(t_data *data, void *filename);
	/*	ft_make_pipeline.c */
int			ft_make_pipeline(t_data *data);
	/*	ft_pipeline_function_set.c */
t_pipeline	*ft_new_pipeline(int (*func)(t_data *, void *),
				void *param, void (*free)());
void		ft_destroy_pipeline(t_pipeline *start);
void		ft_destroy_all_pipelines(t_pipeline ***all);
int			ft_add_pipeline(t_pipeline *prev, int (*func)(t_data *, void *),
				void *param, void (*free)());

//	100_UTILS
/*	ft_free_all.c */
void		ft_free_tab(t_rlines rlines);
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
int			ft_print_export(t_data *data);
void		ft_make_var(t_data *data, t_rlines cmd, t_ints *ints, char *dup);
int			is_greater(char *s1, char *s2);

#endif
