/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolemmen <lolemmen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:59:14 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/20 22:38:11 by lolemmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
