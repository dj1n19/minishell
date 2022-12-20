/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolemmen <lolemmen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:03:44 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/20 22:36:51 by lolemmen         ###   ########.fr       */
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

typedef struct s_cmd
{
	char	*name;
	char	**argv;
	char	**envp;
}	t_cmd;

extern int	g_exit_code;
/*
** builtin
*/
void	b_echo(t_cmd *cmd);
void	b_exit(int n, t_cmd *cmd);
void	b_pwd(void);
void	b_env(char **envp);
char	**b_export(char *env, char **envp);

/*
** utils
*/
void	free_tab(char **tab);
char	**copy_envp(char **envp);
char	*ft_getenv(char *key, char **envp);

/*
** substitution
*/
char	*search_substitution(char *line, t_cmd *cmd);

/*
** split_cmd
*/
char	**split_cmd(char *cmd);

// TEST
// # include "leaks_checker/leaks.h"
// TEST

#endif
