/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:22:03 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 11:04:08 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Count the number of argument present in the input
 * Make sure that every case is taken
 * Example : echo today > outfile is a beautiful > outfile1 day
 * Return the total count : 5
 * "today is a beautiful day"
 */
static	int	nb_arg(char **types, int start, int end)
{
	int	count;

	count = 0;
	while (start < end)
	{
		if (!ft_strcmp(types[start], "WORD"))
		{
			if (!(start > 0 && (!ft_strcmp(types[start - 1], "INPUT")
						|| !ft_strcmp(types[start - 1], "OUTPUT")
						|| !ft_strcmp(types[start - 1], "HEREDOC")
						|| !ft_strcmp(types[start - 1], "APPEND"))))
				count++;
		}
		start++;
	}
	return (count + 1);
}

static int	ft_is_redir(char *type)
{
	if (!ft_strcmp(type, "HEREDOC") || ! ft_strcmp(type, "APPEND")
		|| !ft_strcmp(type, "INPUT") || !ft_strcmp(type, "OUTPUT"))
		return (1);
	return (0);
}

static	int	add_value(t_command *cmd, int *index, char *s)
{
	cmd->args[*index] = ft_strdup(s);
	if (!cmd->args[*index])
		return (1);
	(*index)++;
	return (0);
}

/*
 * Fill a chained list t_command *cmd with every bloc of command present
 * before and after a pipe. Or the only bloc if there is no pipe
 * Do so by checking the struct t_token *tok
 * tok->types get every types of bloc present (WORD, T_PIPE, REDIR)
 * tok->tokens get the value of every types. 
 * Example : echo -> WORD, | -> T_PIPE, < -> REDIR
 */
int	fill_cmd(t_command *cmd, t_shell *s, int i, int end)
{
	int	index;

	index = 0;
	cmd->args = malloc(sizeof(char *) * nb_arg(s->tok->types, i, end));
	if (!cmd->args)
		return (137);
	while (i < end)
	{
		if (!ft_strcmp(s->tok->types[i], "WORD"))
		{
			if (add_value(cmd, &index, s->tok->token[i]) == 1)
				return (137);
		}
		else if (ft_is_redir(s->tok->types[i]) == 1)
		{
			if (fill_redir_parse(cmd, s->tok->types[i], s->tok->token[i + 1]))
				return (137);
			i++;
		}
		i++;
	}
	cmd->args[index] = NULL;
	return (0);
}
