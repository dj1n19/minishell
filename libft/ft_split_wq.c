/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_wq.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 09:48:58 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/13 16:49:57 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*ft_handle_quotes(const char *s, int *count, int has_quote, char c)
{
	if (!has_quote && *s != '"' && *s != c)
	{
		(*count)++;
		while (*s != c)
		{
			if (!*s)
				return (s);
			s++;
		}
	}
	else if (has_quote && *s == '"')
	{
		(*count)++;
		while (*s != '"')
			s++;
	}
	return (s);
}

static int	ft_count_word(const char *s, char c)
{
	int	count;
	int	has_quote;

	count = 0;
	has_quote = 0;
	if (ft_dquote(s))
		has_quote = 1;
	while (*s)
	{
		ft_handle_quotes(s, &count, has_quote, c);
		s++;		
	}
	return (count);
}

static char	*ft_word_extract(const char **s, char c)
{
	char		*word;
	const char	*start;
	int			i;

	start = *s;
	i = 0;
	printf("==> [%s]\n", *s);
	// if (ft_dquote(*s) && **s == '"')
	// {
		// while (*(++*s) && **s != '"')
			// i++;
		// word = ft_substr(start, 1, i);
		// (*s)++;
		// printf("===> [%s]\n", *s);
	// }
	// else
	// {
		while (**s && **s != c)
		{
			if (ft_dquote(*s) && **s == '"')
			{
				while (*(++*s) && **s != '"')
					i++;
				(*s)++;
				printf("===> [%s]\n", *s);
			}
			else
			{
				i++;
				(*s)++;
			}
		}
		if (ft_dquote(start) && *start == '"')
			word = ft_substr(start, 1, i);
		else if (ft_dquote(start))
			word = ft_substr(start, 0, i + 1);
		else
			word = ft_substr(start, 0, i);
	// }
	return (word);
}

static void	ft_free_strings_array(char **strings_array)
{
	while (*strings_array)
		free(*strings_array++);
	free(strings_array);
}

char	**ft_split_wq(char const *s, char c)
{
	char	**strings_array;
	char	**sa_start;

	if (!s)
		return (NULL);
	strings_array = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!strings_array)
		return (NULL);
	sa_start = strings_array;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		*strings_array = ft_word_extract(&s, c);
		if (!*strings_array++)
		{
			ft_free_strings_array(sa_start);
			return (NULL);
		}
		// s += ft_strlen(*strings_array++);
		printf("=> [%s]\n", s);
	}
	*strings_array = NULL;
	return (sa_start);
}
