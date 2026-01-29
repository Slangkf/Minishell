/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 08:20:05 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 11:13:27 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Check if the string is a valid redirection
 * If so, return a type to every corresponding redirection
 * Otherwise 1 
 */
int	ft_isredirec(char *s)
{
	if (!s)
		return (1);
	if (!ft_strcmp(s, "<"))
		return (2);
	if (!ft_strcmp(s, "<<"))
		return (3);
	if (!ft_strcmp(s, ">"))
		return (4);
	if (!ft_strcmp(s, ">>"))
		return (5);
	return (1);
}

/*
 * On the ret value associeted to the type char **, the corresponding
 * Value of the type redirection
 */
static	int	fill_redir(char **types, int ret, int i)
{
	if (ret == 2)
		types[i] = ft_strdup("INPUT");
	else if (ret == 3)
		types[i] = ft_strdup("HEREDOC");
	else if (ret == 4)
		types[i] = ft_strdup("OUTPUT");
	else if (ret == 5)
		types[i] = ft_strdup("APPEND");
	if (!types[i] || !types)
		return (137);
	return (0);
}

static int	give_types_bloc(t_shell *shell, int i, char *t)
{
	int	ret;

	ret = ft_isredirec(t);
	if (ft_strncmp(t, "|", ft_strlen(t)) == 0)
	{
		shell->tok->types[i] = ft_strdup("T_PIPE");
		if (!shell->tok->types[i])
			return (137);
	}
	else if (ret != 1)
	{
		if (fill_redir(shell->tok->types, ret, i) == 137)
			return (137);
	}
	else
	{
		shell->tok->types[i] = ft_strdup("WORD");
		if (!shell->tok->types[i])
			return (137);
	}
	return (0);
}

/*
 * Parse the token splitted input, and determine the right types of
 * each tokens
 */
int	give_types(t_shell *shell)
{
	int		i;
	char	*t;

	i = 0;
	while (shell->tok->token[i])
	{
		t = shell->tok->token[i];
		if (give_types_bloc(shell, i, t) != 0)
			return (137);
		if (shell->tok->types[i] == NULL)
			return (137);
		i++;
	}
	shell->tok->types[i] = ft_strdup("END");
	if (!shell->tok->types[i])
		return (137);
	shell->tok->types[i + 1] = ft_strdup("NULL");
	if (!shell->tok->types[i + 1])
		return (137);
	shell->tok->types[i + 2] = NULL;
	return (0);
}

/*
 * Creation of the struct t_token *tok, splitting of the input (line)
 * Creation of the types and tokens of the *tok struct
 * Verification of the every error and return the write error code
 * 2 if there is an error in the syntax
 * 137 if a memory allocation failed
 */
int	lexer(t_shell *shell, char *line)
{
	shell->tok = malloc(sizeof(t_token));
	if (!shell->tok)
		return (137);
	shell->tok->token = split_custom(line);
	if (!shell->tok->token)
		return (137);
	shell->tok->types = malloc(sizeof(char *)
			* (ft_array_len(shell->tok->token) + 3));
	if (!shell->tok->types)
		return (ft_free_array(shell->tok->token), free(shell->tok), 137);
	if (give_types(shell) == 137)
		return (ft_free_tokens(shell->tok), 137);
	if (main_lexer_verif(shell) != 0)
		return (ft_free_tokens(shell->tok), 2);
	return (0);
}
