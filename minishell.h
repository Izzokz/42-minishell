/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:20:53 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/23 14:34:06 by pboucher         ###   ########.fr       */
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
	t_rlines			envp;
	t_slines			input;
	t_slines			pipeline;
	struct sigaction	usr;
}	t_data;

void		ft_set_path(t_data *data);
char		*ft_get_path(char *filename, char **all_path);
t_slines	ft_pipe_split(char *line);
void		ft_exit_id(t_data *data, int exit_id);
void		ft_exit(t_data *data);
int			ft_make_pipeline(t_data *data);
void		ft_free_all(t_data *data);

#endif
