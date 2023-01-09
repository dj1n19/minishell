/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolemmen <lolemmen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:59:14 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/23 11:57:25 by lolemmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab[i]);
		free(tab);
	}
}

char	**copy_envp(char **envp)
{
	int		i;
	char	**envpc;

	i = 0;
	while (envp[i])
		i++;
	envpc = malloc(sizeof(char *) * (i + 1));
	if (!envpc)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envpc[i] = ft_strdup(envp[i]);
		i++;
	}
	envpc[i] = NULL;
	return (envpc);
}

char	*ft_getenv(char *key, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
		{
			j = 0;
			while (envp[i][j] != '=')
				j++;
			return (&envp[i][j + 1]);
		}
		i++;
	}
	return (NULL);
}

int	has_key(char *env_key, char **envp)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_strjoin(env_key, "=");
	while (envp[i])
	{
		if (!ft_strncmp(key, envp[i], ft_strlen(key)))
		{
			free(key);
			return (i);
		}
		i++;
	}
	free(key);
	return (0);
}
