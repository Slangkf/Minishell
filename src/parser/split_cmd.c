/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:28:51 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 11:08:24 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Create a node of the chained list *cmds with 
 * every bloc of command, args, redir
 * If any malloc as failed return 137 as error
 */
t_command	*build_cmd(t_shell *shell, t_token *tok, int start, int end)
{
	int			ret;
	t_command	*cmd;

	(void)tok;
	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	ret = fill_cmd(cmd, shell, start, end);
	if (ret != 0)
	{
		shell->error = ret;
		return (NULL);
	}
	return (cmd);
}

/*
 * Change to the new node of the chained list *cmds
 */
void	append_cmd(t_command **head, t_command **curr, t_command *new)
{
	if (!*head)
		*head = new;
	else
		(*curr)->next = new;
	*curr = new;
}

/*
 * Main part to split first bloc of the inputed line into a cmd node
 * every time it reach a T_PIPE types
 * or create only one command node if there is no T_PIPE present
 */
static int	parse_create_list(t_shell *shell)
{
	t_command	*head;
	t_command	*curr;
	int			i;
	int			start;

	i = 0;
	start = 0;
	head = NULL;
	while (ft_strcmp(shell->tok->types[i], "NULL"))
	{
		if (!ft_strcmp(shell->tok->types[i], "T_PIPE")
			|| !ft_strcmp(shell->tok->types[i], "END"))
		{
			shell->cmds = build_cmd(shell, shell->tok, start, i);
			if (!shell->cmds)
				return (137);
			append_cmd(&head, &curr, shell->cmds);
			start = i + 1;
		}
		i++;
	}
	shell->cmds = head;
	return (0);
}

/*
 * Check if everything goes well otherwise return the right error code
 */
int	parse(t_shell *shell)
{
	if (parse_create_list(shell) != 0)
	{
		ft_free_tokens(shell->tok);
		free_cmd_list(shell->cmds);
		if (shell->error == 2)
			return (2);
		return (137);
	}
	return (0);
}
