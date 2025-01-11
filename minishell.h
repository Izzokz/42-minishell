/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:20:53 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/11 16:22:42 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "010_FT_PRINTF/ft_printf.h"
# include <stdlib.h>
# include <signal.h>

typedef struct	s_data
{
	char	*line;
	char	**envp;
	struct sigaction	usr;
}	t_data;

#endif