/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:45:21 by seruff            #+#    #+#             */
/*   Updated: 2025/04/08 13:40:55 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_words(const char *s, char c)
{
	size_t	i;
	int		count;
	int		in_w;

	count = 0;
	in_w = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c && in_w == 0)
		{
			count++;
			in_w = 1;
		}
		if (s[i] == c)
			in_w = 0;
		i++;
	}
	return (count);
}

static	char	*ft_extract(const char *s, char c, size_t *i)
{
	size_t	start;

	if (!s)
		return (NULL);
	while (s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	return (ft_substr(s, start, *i - start));
}

static void	dest_null(char **dest, int words)
{
	while (words--)
		free(dest[words]);
	free(dest);
}

char	**ft_split(const char *s, char c)
{
	size_t	i;
	int		words;
	int		index;
	char	**dest;

	words = count_words(s, c);
	index = 0;
	i = 0;
	dest = malloc((words + 1) * sizeof(char *));
	if (!s || !dest)
		return (NULL);
	while (index < words)
	{
		dest[index] = ft_extract(s, c, &i);
		if (!dest[index++])
		{
			dest_null(dest, index - 1);
			return (NULL);
		}
	}
	dest[index] = NULL;
	return (dest);
}
/*
int	main()
{

	char **result = ft_split("echo test a moi meme; exit", ':');

	if (result)
	{
	 	int	i;

		i = 0;
		while (result[i] != NULL)
		{
			printf ("%s \n", result[i]);
			i++;
		}

		//Liberer la memoire allouee par ft_split
	}
	else
		printf("Erreur memoire.");
	return (0);
}*/
