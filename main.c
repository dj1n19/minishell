/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dj1n <dj1n@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:03:34 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/17 00:14:07 by dj1n             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**parse_cmd(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->name, "exit", 5))
		b_exit(g_exit_code, cmd);
	else if (!ft_strncmp(cmd->name, "echo", 5))
		b_echo(cmd);
	else if (!ft_strncmp(cmd->name, "pwd", 4))
		b_pwd();
	else if (!ft_strncmp(cmd->name, "env", 4))
		b_env(cmd->envp);
	else if (!ft_strncmp(cmd->name, "export", 7))
	{
		if (cmd->argv)
			cmd->envp = b_export(ft_strdup(*cmd->argv), cmd->envp);
	}
	else
	{
		printf("minishell 🙊 => %s: command not found\n", cmd->name);
		g_exit_code = 127;
	}
	return (cmd->envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*line;	
	t_cmd	cmd;
	char	**cmdv;

	(void)argc;
	(void)argv;
	g_exit_code = 0;
	cmd.envp = copy_envp(envp);
	if (!cmd.envp)
		b_exit(2, &cmd);
	while (1)
	{
		prompt = getenv("PWD");
		prompt = ft_strjoin(prompt, " ~> ");
		line = readline(prompt);
		line = search_substitution(line, &cmd);
		free(prompt);
		cmdv = split_cmd(line);
		// TEST
		for(int i=0;cmdv[i];i++)
			printf("-->%s\n", cmdv[i]);
		// TEST
		free(line);
		if (!cmdv)
			b_exit(1, &cmd);
		cmd.name = cmdv[0];
		if (cmdv[1])
			cmd.argv = &cmdv[1];
		else
			cmd.argv = NULL;
		cmd.envp = parse_cmd(&cmd);
		free(cmdv);
	}
	return (0);
}
