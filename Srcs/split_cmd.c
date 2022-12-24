/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolemmen <lolemmen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:29:48 by lolemmen          #+#    #+#             */
/*   Updated: 2022/12/23 11:57:05 by lolemmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int	has_closed_quotes(char *cmd)
{
	int	count;

	count = 0;
	while (cmd && *cmd)
	{
		if (*cmd == '"')
			count++;
		cmd++;
	}
	if (count > 1)
		return (1);
	return (0);
}

static int	count_word(char *cmd)
{
	int	count;

	count = 0;
	while (cmd && *cmd)
	{
		while (*cmd && *cmd == ' ')
			cmd++;
		if (*cmd == 0)
			return (count);
		count++;
		while (*cmd && *cmd != ' ')
		{
			if (*cmd == '"' && has_closed_quotes(cmd))
			{
				cmd++;
				while (*cmd && *cmd != '"')
					cmd++;
				if (*cmd == 0)
					return (count);
			}
			cmd++;
		}
	}
	return (count);
}

static char	*substring(char *cmd)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (cmd[i] && cmd[i] != ' ')
	{
		if (cmd[i] == '"' && has_closed_quotes(cmd))
		{
			while (cmd[i] && cmd[++i] != '"')
				;
		}
		i++;
	}
	str = (char *) malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	while (j < i)
		str[j++] = *cmd++;
	str[j] = 0;
	return (str);
}

static void	free_scmd(char **scmd)
{
	while (scmd && *scmd)
		free(*scmd++);
	free(scmd);
}

char	**split_cmd(char *cmd)
{
	char	**scmd;
	char	**save;
	int		count;

	count = count_word(cmd);
	scmd = (char **) malloc(sizeof(char *) * (count + 1));
	if (!scmd || !count)
		return (NULL);
	save = scmd;
	while (*cmd)
	{
		while (*cmd && *cmd == ' ')
			cmd++;
		if (*cmd == 0)
			break ;
		*scmd = substring(cmd);
		if (!*scmd)
		{
			free_scmd(save);
			return (NULL);
		}
		cmd += ft_strlen(*scmd++);
	}
	*scmd = NULL;
	return (save);
}
