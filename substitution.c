/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:10:41 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/08 19:16:15 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_key(char *str)
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

static char	*substitute_env(char *line, char *env_offset, char *env_key, t_cmd *cmd)
{
	char	*env_value;
	char	*buf;
	char	*sub_line;
	char	*line_env_offset;

	env_value = ft_getenv(env_key, cmd->envp);
	if (!env_value)
		env_value = "";
	buf = ft_strjoin(env_value, env_offset + ft_strlen(env_key) + 1);
	line_env_offset = ft_strnstr(line, env_offset, ft_strlen(line));
	if (line_env_offset)
		*line_env_offset = 0;
	sub_line = ft_strjoin(line, buf);
	free(buf);
	free(line);
	return (sub_line);
}

static char	*substitute_question_mark(char *line, char *qm_offset)
{
	char	*buf;
	char	*sub_line;
	char	*line_qm_offset;
	char	*exit_code;

	exit_code = ft_itoa(g_exit_code);
	buf = ft_strjoin(exit_code, qm_offset + 2);
	line_qm_offset = ft_strnstr(line, qm_offset, ft_strlen(line));
	if (line_qm_offset)
		*line_qm_offset = 0;
	sub_line = ft_strjoin(line, buf);
	free(exit_code);
	free(buf);
	free(line);
	return (sub_line);
}

char	*search_substitution(char *line, t_cmd *cmd)
{
	char	*key;
	char	*sub_line;
	char	*save;

	save = line;
	sub_line = ft_strdup(line);
	while (*line)
	{
		if (*line == '$')
		{
			if (*(line + 1) == '?')
				sub_line = substitute_question_mark(sub_line, line++);
			else
			{
				key = extract_key(line);
				sub_line = substitute_env(sub_line, line, key, cmd);
				line += ft_strlen(key);
				free(key);
			}
		}
		line++;
	}
	free(save);
	return (sub_line);
}
