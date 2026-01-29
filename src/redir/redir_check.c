/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:08:53 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 10:57:59 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Treat the information on the number of infiles present in the input
 * If there is multiple we only should send the output of the command 
 * into the last outfile
 * We keep the others to create if they exist and need to be created or not
 * c->last_in & c->last_out should have the position of the last input and output
 */
static void	fill_infiles_nb(t_command *c)
{
	int	i;

	i = 0;
	c->nb_infiles = 0;
	while (i < c->nb_files)
	{
		if (c->files[i].mode == 0 || c->files[i].mode == 1)
			c->nb_infiles++;
		i++;
	}
	c->nb_outfiles = c->nb_files - c->nb_infiles;
	if (c->nb_outfiles < 0)
		c->nb_outfiles = 0;
	if (c->nb_infiles < 0)
		c->nb_infiles = 0;
	if (c->nb_files == 0)
	{
		c->nb_infiles = 0;
		c->nb_outfiles = 0;
		c->last_in = -1;
		c->last_out = -1;
	}
}

static void	fill_last_infile(t_command *c)
{
	int	i;

	i = c->nb_files - 1;
	c->last_in = -1;
	while (i >= 0)
	{
		if (c->files[i].mode == 0 || c->files[i].mode == 1)
		{
			c->last_in = i;
			c->files[i].f_last_in = 1;
			break ;
		}
		i--;
	}
}

static void	fill_last_outfile(t_command *c)
{
	int	i;

	i = c->nb_files - 1;
	c->last_out = -1;
	while (i >= 0)
	{
		if (c->files[i].mode == 2 || c->files[i].mode == 3)
		{
			c->last_out = i;
			c->files[i].f_last_out = 1;
			break ;
		}
		i--;
	}
}

void	check_redir(t_shell *shell)
{
	t_command	*current;

	current = shell->cmds;
	while (current)
	{
		fill_infiles_nb(current);
		fill_last_infile(current);
		fill_last_outfile(current);
		current = current->next;
	}
}
