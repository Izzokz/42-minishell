/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:20:53 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/01 15:39:27 by pboucher         ###   ########.fr       */
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

/* Prompt of Minishell */
# define MI "\1\e[1;34m\2[\1\e[1;31m\2m\1\e[1;32m\2i"
# define NI "\1\e[1;33m\2n\1\e[1;34m\2i\1\e[1;35m\2PK\1\e[1;34m]\2"
# define USER "\1\e[1;33m\2@"
# define SHLVL " \1\e[1;32m\2[Lv. "
# define PBEG " \1\e[1;35m\2{"
# define PEND "} \1\e[1;31m\2»\1\e[0m\2 "

/* All Error MSG, expect Internal Errors */
# define ERROR_CD "\e[1;31m[Minishell] \e[0mcd: %s: No such file or directory\n"
# define ERROR_TMA "\e[1;31m[Minishell] \e[0mToo many arguments\n"
# define ERROR_CCH "\e[1;31m[Minishell] \e[0mCannot create history\n"
# define ERROR_UQ "\e[1;31m[Minishell] \e[0mUnfinished quotes\n%*."
# define ERROR_FDE "\e[1;31m[Minishell] \e[0m%s doesn't exist\n"
# define ERROR_FNF "\e[1;31m[Minishell] \e[0m%s: not found\n"
# define ERROR_NV "\e[1;31m[Minishell] \e[0m%s: not valid\n"
# define ERROR_NVI "\e[1;31m[Minishell] \e[0mNot a valid identifier\n"
# define ERROR_NEA "\e[1;31m[Minishell] \e[0mNot enough arguments\n%*."

struct	s_pipeline;

typedef struct s_data
{
	char				*user;
	char				*line;
	char				**path;
	char				*history;
	int					bcase;
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
	/*	main.c */
int			is_env_var(char *var, char **envp);
void		ft_get_user(t_data *data);
	/*	ft_history.c */
void		ft_gen_history(t_data *data);
void		ft_add_history(t_data *data);
	/*	ft_utils.c*/
int			set_data(t_data *data, char **envp);
char		*ft_generate_prompt(t_data *data, char *path);
char		*ft_generate_path(t_data *data);
void		up_shlvl(t_data *data);
void		ft_show_prompt(t_data *data);
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
int			ft_free_line(t_data *data);
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
