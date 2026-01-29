/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:23:30 by seruff            #+#    #+#             */
/*   Updated: 2025/06/25 15:53:19 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 * Processes heredoc delimiter - removes quotes and sets expand flag
 * Returns the cleaned delimiter
 */
char	*ft_check_delimiter(t_shell *shell, t_file *current, char *s)
{
	char	*d;

	if (ft_count_carac(s, '\'') > 0 || ft_count_carac(s, '"') > 0)
	{
		d = filter_string(s);
		if (!d)
		{
			shell->error = 137;
			return (NULL);
		}
		s = d;
		current->expand = 1;
		return (s);
	}
	else
		return (s);
}

/*
 * Expands variables in heredoc lines if expansion is needed
 * Returns the expanded string
 */
static char	*expand_delim(t_shell *s, char *line)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	res = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			s->sq = 0;
			tmp = expand_dollar(s, line, &i);
			res = append_str(res, tmp, ft_strlen(tmp));
			free(tmp);
			continue ;
		}
		res = append_str(res, &line[i], 1);
		i++;
	}
	return (free(line), res);
}

/*
 * Checks if heredoc content should be expanded based on delimiter quotes
 * Returns expanded or original line
 */
char	*ft_check_expand(t_shell *shell, t_file *current, char *line)
{
	char	*d;

	if (current->expand == 0)
	{
		d = expand_delim(shell, line);
		if (!d)
		{
			shell->error = 137;
			return (NULL);
		}
		line = d;
		return (line);
	}
	else
		return (line);
}
