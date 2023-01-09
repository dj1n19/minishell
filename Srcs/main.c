/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolemmen <lolemmen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:03:34 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/23 12:13:42 by lolemmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

// int	exit_code = 0;
t_cmd	*g_cmd = NULL;

static char	**parse_cmd(void)
{
	if (!ft_strncmp(g_cmd->name, "exit", 5))
		b_exit(g_cmd->exit_code);
	else if (!ft_strncmp(g_cmd->name, "echo", 5))
		b_echo();
	else if (!ft_strncmp(g_cmd->name, "pwd", 4))
		b_pwd();
	else if (!ft_strncmp(g_cmd->name, "env", 4))
		b_env(g_cmd->envp);
	else if (!ft_strncmp(g_cmd->name, "export", 7))
	{
		if (g_cmd->argv)
			g_cmd->envp = b_export(*(g_cmd->argv + 1), g_cmd->envp);
	}
	else if (!ft_strncmp(g_cmd->name, "unset", 6))
	{
		if (g_cmd->argv)
			g_cmd->envp = b_unset(*(g_cmd->argv + 1), g_cmd->envp);
	}
	else
	{
		printf("minishell 🙊 => %s: command not found\n", g_cmd->name);
		g_cmd->exit_code = 127;
	}
	return (g_cmd->envp);
}

__attribute__((constructor))
void	init(void)
{
	g_cmd = malloc(sizeof(t_cmd));
	if (!g_cmd)
		exit(EXIT_FAILURE);
	g_cmd->exit_code = 0;
	g_cmd->name = NULL;
	g_cmd->argv = NULL;
	g_cmd->envp = NULL;
}

__attribute__((destructor))
void	finish(void)
{
	if (g_cmd)
	{
		if (g_cmd->argv)
			free_tab(g_cmd->argv);
		if (g_cmd->envp)
			free_tab(g_cmd->envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*line;
	// t_cmd	cmd;
	char	**cmdv;

	(void)argc;
	(void)argv;
	//exit_code = 0;
	g_cmd->envp = copy_envp(envp);
	if (!g_cmd->envp)
		b_exit(2);
	while (1)
	{
		prompt = getenv("PWD");
		prompt = ft_strjoin(prompt, " ~> ");
		line = readline(prompt);
		line = search_substitution(line);
		free(prompt);
		cmdv = split_cmd(line);
		// TEST
		for(int i=0;cmdv[i];i++)
			printf("-->%s\n", cmdv[i]);
		// TEST
		free(line);
		if (!cmdv)
			b_exit(1);
		g_cmd->name = cmdv[0];
		g_cmd->argv = cmdv;
		g_cmd->envp = parse_cmd();
		free_tab(cmdv);
	}
	return (0);
}
