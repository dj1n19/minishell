/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:59:14 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/08 19:26:31 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab[i]);
	free(tab - 1);
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
		envpc[i] = envp[i];
		i++;
	}
	envpc[i] = NULL;
	return (envpc);
}

char	*ft_getenv(char *key, char **envp)
{
	printf("===%s\n", key);
	while (*envp)
	{
		if (!ft_strncmp(*envp, key, ft_strlen(key)))
		{
			while (**envp != '=')
				(*envp)++;
			(*envp)++;
			return (*envp);
		}
		envp++;
	}
	return(NULL);
}