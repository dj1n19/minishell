/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolemmen <lolemmen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:03:40 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/23 11:56:53 by lolemmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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

void	b_echo(void)
{
	int	i;
	int	j;
	int	nl;

	i = 1;
	nl = 0;
	while (g_cmd->argv[i])
	{
		if (g_cmd->argv[i][0] == '-')
		{
			j = 1;
			while (g_cmd->argv[i][j] == 'n')
				j++;
			if (g_cmd->argv[i][j] != 0)
				break ;
			if (j > 1)
				nl++;
		}
		else
			break ;
		i++;
	}
	echo_print(&g_cmd->argv[i], nl);
	g_cmd->exit_code = 0;
}

void	b_exit(int n)
{
	// if (g_cmd->argv)
	// 	free_tab(g_cmd->argv - 1);
	// if (g_cmd->envp)
	// 	free_tab(g_cmd->envp);
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
	printf("envp size: %d\n", i + 1);
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
		free(env_key);
		return (new_envp);
	}
}

char	**b_unset(char *env_key, char **envp)
{
	int		i;
	char	**new_envp;

	if (!env_key || !envp)
		return (envp);
	i = has_key(env_key, envp);
	while (envp[i])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	new_envp = realloc(envp, sizeof(char *) * i);
	if (!new_envp)
		return (envp);
	return (new_envp);
}