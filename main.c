/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:03:34 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/08 17:53:38 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_cmd(t_cmd *cmd)
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
		cmd->envp = export(ft_strdup(*cmd->argv), cmd->envp);
	else
	{
		printf("minishell 🙊 => %s: command not found\n", cmd->name);
		g_exit_code = 127;
	}
	return (0);
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
		line = search_substitution(line);
		free(prompt);
		cmdv = ft_split(line, ' ');
		free(line);
		if (!cmdv)
			b_exit(1, &cmd);
		cmd.name = cmdv[0];
		cmd.argv = &cmdv[1];
		if (parse_cmd(&cmd) == -1)
			b_exit(1, &cmd);
		free_tab(cmd.argv);
	}
	return (0);
}
