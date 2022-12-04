/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:03:44 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/04 18:18:07 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

int g_exit_code;

typedef struct s_cmd
{
    char    *name;
    char    **argv;
}   t_cmd;

/* 
** builtin
*/
void    b_echo(t_cmd *cmd);
void    b_exit(int n);

#endif