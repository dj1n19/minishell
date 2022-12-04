/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:03:34 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/04 18:25:11 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char *extract_key(char *str)
{
	char	*key;
	size_t	i;

	i = 0;
	str++;
	while (str[i] && str[i] != ' ' && str[i] != '$')
	{
		i++;
	}
	key = ft_substr(str, 0, i);
	return (key);
}

static char *substitute_env(char *line, char *env_offset, char *env_key)
{
	char 	*env_value;
	char	*buf;
	char	*sub_line;

	env_value = getenv(env_key);
	if (!env_value)
		env_value = "";
	buf = ft_strjoin(env_value, env_offset + ft_strlen(env_key) + 1);
	*env_offset = 0;
	sub_line = ft_strjoin(line, buf);
	free(buf);
	return (sub_line);
}

static char	*substitute_question_mark(char *line, char *qm_offset)
{
	char	*buf;
	char	*sub_line;

	buf = ft_strjoin(ft_itoa(g_exit_code), qm_offset + 2);
	*qm_offset = 0;
	sub_line = ft_strjoin(line, buf);
	free(buf);
	return (sub_line);	
}

static char	*search_substitution(char *line)
{
	char	*key;
	char	*sub_line;

	sub_line = line;
	while (*line)
	{
		if (*line == '$')
		{
			printf("line: %s\n", line);
			if (*(line + 1) == '?')
			{
				sub_line = substitute_question_mark(sub_line, line);
				line++;
			}
			else
			{
				key = extract_key(line);
				sub_line = substitute_env(sub_line, line, key);
				line += ft_strlen(key);
			}
		}
		line++;
	}
	return (sub_line);
}

static int	parse_cmd(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->name, "exit", 5))
		b_exit(g_exit_code);
	else if (!ft_strncmp(cmd->name, "echo", 5))
		b_echo(cmd);
	else
	{
		printf("minishell 🙊 => %s: command not found\n", cmd->name);
		g_exit_code = 127;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*line;	
	t_cmd	cmd;
	char	**cmdv;

	g_exit_code = 0;
	while (1)
	{
		prompt = getenv("PWD");
		prompt = ft_strjoin(prompt, " ~> ");
		line = readline(prompt);
		line = search_substitution(line);
		printf("->%s\n", line);
		free(prompt);
		cmdv = ft_split(line, ' ');
		if (!cmdv)
			break;
		cmd.name = cmdv[0];
		cmd.argv = &cmdv[1];
		if (parse_cmd(&cmd) == -1)
			break ;
	}
	free(line);
	return (0);
}