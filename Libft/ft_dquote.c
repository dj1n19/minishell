/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dquote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolemmen <lolemmen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:25:47 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/20 22:39:42 by lolemmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dquote(const char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '"')
			i++;
		str++;
	}
	return (!(i % 2));
}
