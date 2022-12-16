/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dj1n <dj1n@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:03:40 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/17 00:14:27 by dj1n             ###   ########.fr       */
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
		free_tab(cmd->argv - 1);
	if (cmd->envp)
		free_tab(cmd->envp);
	// check_leaks();
	exit((unsigned int)n);
}

void	b_pwd(void)
{
	printf("%s\n", getenv("PWD"));
}

void	b_env(char **envp)
{
	// TEST
	int i = 0;

	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
		i++; // TEST
	}

	//TEST
	printf("envp size: %d\n", i);
}

char	**b_export(char *env, char **envp)
{
	int		i;
	char	**new_envp;
	char	*env_key;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if ((size_t)i == ft_strlen(env))
		return (envp);
	env_key = ft_substr(env, 0, i);
	printf("env_key: %s\n", env_key);
	if (ft_getenv(env_key, envp))
	{
		i = 0;
		while (envp[i] && ft_strncmp(envp[i], env, ft_strlen(env_key) + 1))
			i++;
		free(envp[i]);
		envp[i] = ft_strdup(env);
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
		new_envp[i] = ft_strdup(env);
		new_envp[i + 1] = NULL;
		return (new_envp);
	}
}