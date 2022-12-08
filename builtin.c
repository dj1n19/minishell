/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:03:40 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/08 17:56:10 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_print(char **args, int nl)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	if (!nl)
		printf("\n");
}

void	b_echo(t_cmd *cmd)
{
	int	i;
	int	j;
	int	nl;

	i = 0;
	nl = 0;
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] == '-')
		{
			j = 1;
			while (cmd->argv[i][j] == 'n')
				j++;
			if (cmd->argv[i][j] != 0)
				break ;
			if (j > 1)
				nl++;
		}
		else
			break ;
		i++;
	}
	echo_print(&cmd->argv[i], nl);
	g_exit_code = 0;
}

void	b_exit(int n, t_cmd *cmd)
{
	if (cmd->argv)
		free_tab(cmd->argv);
	if (cmd->envp)
		free_tab(cmd->envp);
	check_leaks();
	exit((unsigned int)n);
}

void	b_pwd(void)
{
	printf("%s\n", getenv("PWD"));
}

void	b_env(char **envp)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}

char	**export(char *env, char **envp)
{
	int		i;
	char	**new_envp;
	char	*env_key;

	i = 0;
	while (env[i] != '=')
		i++;
	env_key = ft_substr(env, 0, i);
	printf(">>%s\n", getenv("GNAH"));
	if (getenv(env_key))
	{
		i = 0;
		while (ft_strncmp(envp[i], env_key, ft_strlen(env_key)))
			i++;
		envp[i] = env;
		free(env_key);
		return (envp);
	}
	else
	{
		i = 0;
		while (envp[i])
			i++;
		new_envp = realloc(envp, sizeof(char *) * (i + 2));
		if (!new_envp)
			return (NULL);
		new_envp[i] = env;
		new_envp[i + 1] = NULL;
		return (new_envp);
	}
}