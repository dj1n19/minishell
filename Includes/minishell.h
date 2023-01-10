/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolemmen <lolemmen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:03:44 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/23 16:18:29 by lolemmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"

typedef enum e_tokens
{
	QUOTES = 0x1,
	DQUOTES = 0x2,
	PIPE = 0x4,
	REDIR = 0x8,
}	t_tokens;

typedef struct s_cmd
{
	char	*name;
	char	**argv;
	char	**envp;
	char	tokens;
	int		exit_code;
}	t_cmd;

// extern int	exit_code;

extern struct s_cmd	*g_cmd;

/*
* builtin
*/
void	b_echo(void);
void	b_exit(int n);
void	b_pwd(void);
void	b_env(char **envp);
char	**b_export(char *env, char **envp);
char	**b_unset(char *env_key, char **envp);

/*
* utils
*/
void	free_tab(char **tab);
char	**copy_envp(char **envp);
char	*ft_getenv(char *key, char **envp);
int		has_key(char *env_key, char **envp);

/*
* substitution
*/
char	*search_substitution(char *line);

/*
* split_cmd
*/
char	**split_cmd(char *cmd);

/*
* parsing
*/
void	search_tokens(void);

// TEST
// # include "leaks_checker/leaks.h"
// TEST

#endif
