/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:04:07 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 11:05:22 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Fill the chained list of redirection present in shell->cmds->files
 * For < INFILE > OUTFILE >> APPEND
 */
static int	fill_redir_file(t_command *cmd, char *file, int type)
{
	cmd->files[cmd->nb_files].delimiter = NULL;
	cmd->files[cmd->nb_files].mode = type;
	cmd->files[cmd->nb_files].expand = 0;
	cmd->files[cmd->nb_files].f_last_in = -1;
	cmd->files[cmd->nb_files].f_last_out = -1;
	cmd->files[cmd->nb_files].file = ft_strdup(file);
	if (!cmd->files[cmd->nb_files].file)
		return (137);
	cmd->nb_files++;
	return (0);
}

/*
 * Fill the chained list of redirection present in shell->cmds->files
 * For << HEREDOC
 */
static int	fill_redir_here(t_command *cmd, char *file)
{
	cmd->files[cmd->nb_files].mode = 0;
	cmd->files[cmd->nb_files].expand = 0;
	cmd->files[cmd->nb_files].file = NULL;
	cmd->files[cmd->nb_files].f_last_in = -1;
	cmd->files[cmd->nb_files].f_last_out = -1;
	cmd->files[cmd->nb_files].delimiter = ft_strdup(file);
	if (!cmd->files[cmd->nb_files].delimiter)
		return (137);
	cmd->nb_files++;
	return (0);
}

static int	fill_redir(t_command *cmd, char *file, int type)
{
	t_file	*new;

	new = ft_realoc(cmd->files, sizeof(t_file) * (cmd->nb_files),
			sizeof(t_file) * (cmd->nb_files + 1));
	if (!new)
		return (137);
	cmd->files = new;
	if (type == 0)
	{
		if (fill_redir_here(cmd, file) != 0)
			return (137);
	}
	else
	{
		if (fill_redir_file(cmd, file, type) != 0)
			return (137);
	}
	return (0);
}

int	fill_redir_parse(t_command *cmd, char *word, char *file)
{
	if (!ft_strcmp(word, "HEREDOC"))
		return (fill_redir(cmd, file, 0));
	else if (!ft_strcmp(word, "INPUT"))
		return (fill_redir(cmd, file, 1));
	else if (!ft_strcmp(word, "OUTPUT"))
		return (fill_redir(cmd, file, 2));
	else if (!ft_strcmp(word, "APPEND"))
		return (fill_redir(cmd, file, 3));
	return (0);
}
