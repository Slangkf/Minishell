/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:51:20 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 11:18:13 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*handle_error(t_shell *shell, int *i)
{
	char	*output;
	char	*tmp;

	output = NULL;
	tmp = ft_itoa(shell->error);
	if (!tmp)
		return (NULL);
	*i += 2;
	output = append_str(NULL, tmp, ft_strlen(tmp));
	free(tmp);
	if (!output)
		return (NULL);
	return (output);
}

/*
 * Handle case with multiple $$ consecutive
 */
static char	*handle_special_cases(const char *input, int *i, int in_q)
{
	if (input[*i + 1] == '$')
	{
		*i += 2;
		return (append_str(NULL, "$$", 2));
	}
	if (is_quote(input[*i + 1]))
	{
		if (in_q == 1)
		{
			(*i)++;
			return (append_char(NULL, '$'));
		}
		(*i)++;
		return (ft_strdup(""));
	}
	return (NULL);
}

/*
 * Remove from the token the value of the KEY is this one is invalid
 * Such as a key not corresponding to the environnement or a wrong format
 * Without removing every thing from this same token
 * Example : $9HOME -> $9 doesn't exist 
 * Return -> ""HOME
 */
static char	*handle_invalid_var(const char *input, int *i)
{
	if (ft_isdigit(input[*i + 1]))
	{
		*i += 2;
		return (ft_strdup(""));
	}
	(*i)++;
	return (append_char(NULL, '$'));
}

static char	*handle_normal_var(t_shell *shell, const char *input, int *i)
{
	char	*tmp;
	char	*output;

	(*i)++;
	tmp = expand_var(shell, input, i);
	if (!tmp)
		return (NULL);
	output = append_str(NULL, tmp, ft_strlen(tmp));
	return (free(tmp), output);
}

char	*expand_dollar(t_shell *shell, const char *input, int *i)
{
	int		in_quote;
	char	*res;
	char	*res_error;

	in_quote = 0;
	in_quote = is_in_quote(shell);
	if (input[*i + 1] == '?')
	{
		res_error = handle_error(shell, i);
		return (res_error);
	}
	res = handle_special_cases(input, i, in_quote);
	if (res)
		return (res);
	if (!is_var_start(input[*i + 1]))
		return (handle_invalid_var(input, i));
	return (handle_normal_var(shell, input, i));
}
