/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:07:44 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 10:56:26 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Handle the case of a present redirection into the command line
 * Isolate it or split it if necessary such as <<< -> << < into two tokens
 * for syntax error
 * Or <<heredoc_delimiter -> << heredoc_delimiter
 * To help into the parser bloc functions
 */
static int	handle_operator(const char *line, int *i, char **tokens, int *j)
{
	if ((line[*i] == '<' && line[*i + 1] == '<')
		|| (line[*i] == '>' && line[*i + 1] == '>'))
	{
		tokens[(*j)] = ft_strndup(&line[*i], 2);
		if (!tokens[(*j)])
			return (137);
		(*j)++;
		*i += 2;
	}
	else
	{
		tokens[(*j)] = ft_strndup(&line[(*i)++], 1);
		if (!tokens[(*j)])
			return (137);
		(*j)++;
	}
	return (0);
}

/*
 * Does the same as before for every words
 */
static int	handle_word(const char *line, int *i, char **tokens, int *j)
{
	int		start;
	int		k;
	char	quote;

	start = *i;
	k = *i;
	while (line[k] && !ft_isspace(line[k]) && !ft_is_operator(line[k]))
	{
		if (line[k] == '\'' || line[k] == '"')
		{
			quote = line[k++];
			while (line[k] && line[k] != quote)
				k++;
			if (line[k] == quote)
				k++;
		}
		else
			k++;
	}
	tokens[(*j)] = ft_strndup(&line[start], k - start);
	if (!tokens[(*j)++])
		return (137);
	*i = k;
	return (0);
}

static	int	bloc_split(char **tokens, const char *line, int *i, int *j)
{
	if (ft_is_operator(line[*i]))
	{
		if (handle_operator(line, i, tokens, j) != 0)
			return (137);
	}
	else
	{
		if (handle_word(line, i, tokens, j) != 0)
			return (137);
	}
	return (0);
}

/*
 * Dirty one to only handle a Maximum of tokens and don't go way over the 
 * desired size. 
 * Splitting the input into tokens in char ** with one token
 * one word, one bloc quoted, one redirection kind, one pipe.
 */
static char	**split_dirty_custom(const char *line)
{
	int		i;
	int		j;
	char	**tokens;

	tokens = malloc(sizeof(char *) * MAX_TOKEN);
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else
		{
			if (bloc_split(tokens, line, &i, &j) != 0)
				return (NULL);
		}
	}
	tokens[j] = NULL;
	return (tokens);
}

/*
 * Clean it to adapt the final char ** to the real size of the tokenization
 */
char	**split_custom(const char *line)
{
	int		i;
	char	**token;
	char	**result_token;

	i = 0;
	token = split_dirty_custom(line);
	if (!token)
		return (NULL);
	result_token = malloc(sizeof(char *) * (ft_array_len(token) + 1));
	if (!result_token)
		return (ft_free_array(token), NULL);
	while (i < (int)ft_array_len(token) && token[i])
	{
		result_token[i] = ft_strdup(token[i]);
		if (!result_token[i])
		{
			ft_free_array(token);
			return (ft_free_array(result_token), NULL);
		}
		i++;
	}
	result_token[i] = NULL;
	ft_free_array(token);
	return (result_token);
}
