/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:52:22 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 11:14:21 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	char	*cleaning_action(char *s, char *out, int *i, int *j)
{
	char	q;

	out = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!out)
		return (NULL);
	while (s[*i])
	{
		if (s[*i] == '\'' || s[(*i)] == '"')
		{
			q = s[(*i)++];
			while (s[*i] && s[*i] != q)
				out[(*j)++] = s[(*i)++];
			if (s[*i] == q)
				(*i)++;
		}
		else
			out[(*j)++] = s[(*i)++];
	}
	out[(*j)] = '\0';
	return (out);
}

/*
 * Remove the quotes inside a non quoted bloc or remove the quotes outside a bloc
 * Without removing the quotes inside a quoted bloc
 */
char	*clean_quotes(char *s)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	j = 0;
	out = NULL;
	if (!s)
		return (NULL);
	out = cleaning_action(s, out, &i, &j);
	if (!out)
		return (free(s), NULL);
	return (out);
}
