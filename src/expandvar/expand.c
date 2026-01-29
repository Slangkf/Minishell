/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:21:33 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 11:16:12 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Expand the value of the key variable depend on the environnement
 * Replace KEY to VALUE
 * If it's possible
 */
char	*expand_var(t_shell *shell, const char *line, int *i)
{
	int		j;
	char	var[256];
	char	*value;
	char	*tmp;

	j = 0;
	while (is_var_char(line[*i + j]) && j < 256)
	{
		var[j] = line[*i + j];
		j++;
	}
	var[j] = '\0';
	value = give_env_value(shell->environ, var);
	*i += j;
	if (!value || !*value)
		return (ft_strdup(""));
	tmp = ft_strdup(value);
	return (free(value), tmp);
}

/*
 * Get information one the type of quotation around a variable possibly expanded
 * If it's into single quote the variable shouldn't be expanded
 * Otherwise without quotes or into double quotes it should be expanded
 */
static	void	hand_quote(t_shell *shell, char line)
{
	if (line == '\'' && !shell->dq)
		shell->sq = !shell->sq;
	else if (line == '"' && !shell->sq)
		shell->dq = !shell->dq;
}

char	*expand(t_shell *s, char *line)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	s->sq = 0;
	s->dq = 0;
	res = NULL;
	while (line[i])
	{
		hand_quote(s, line[i]);
		if ((line[i] == '\'' && !s->dq) || (line[i] == '"' && !s->sq))
			res = append_str(res, &line[i], 1);
		else if (line[i] == '$' && ((!s->sq && s->dq) || (!s->sq && !s->dq)))
		{
			tmp = expand_dollar(s, line, &i);
			res = append_str(res, tmp, ft_strlen(tmp));
			free(tmp);
			continue ;
		}
		else
			res = append_str(res, &line[i], 1);
		i++;
	}
	return (free(line), res);
}
