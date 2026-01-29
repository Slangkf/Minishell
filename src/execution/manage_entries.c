/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_entries.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclouet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:51:16 by tclouet           #+#    #+#             */
/*   Updated: 2025/06/17 10:26:01 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Opens an input file and redirects STDIN if it's the last input redirection
 * Returns 0 on success, -1 if file not found
 */
int	ft_infile_mode(t_command *current, t_file *infile)
{
	int	infile_fd;

	infile_fd = open(infile->file, O_RDONLY);
	if (infile_fd == -1)
		return (ft_no_file_or_directory(infile->file), -1);
	if (infile->f_last_in == 1)
	{
		if (current->entry_fd != -1)
			close(current->entry_fd);
		current->entry_fd = -1;
		if (dup2(infile_fd, STDIN_FILENO) == -1)
			return (ft_print_error("dup2 error\n"), -1);
		current->infile_dup = 1;
		return (0);
	}
	close(infile_fd);
	return (0);
}

/*
 * Processes all input and output files for a command in a pipeline
 * Returns 0 on success, -1 on error
 */
static int	manage_files_in_pipe(t_command *current)
{
	int	i;

	i = 0;
	while (i < current->nb_files)
	{
		if (current->files[i].mode == 1)
		{
			if (ft_infile_mode(current, &current->files[i]) == -1)
				return (-1);
		}
		else if (current->files[i].mode == 2 || current->files[i].mode == 3)
		{
			if (ft_outfile_mode(current, &current->files[i],
					current->files[i].mode) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

/*
 * Manages input redirection for a command (files or previous pipe)
 * Returns 0 on success, -1 on error
 */
int	ft_manage_entries(t_shell *shell, t_command *current, int prev_pipe_fd)
{
	if (current->nb_files)
	{
		if (manage_files_in_pipe(current) == -1)
		{
			ft_free_program(shell);
			exit (1);
		}
	}
	if (current->entry_fd != -1)
	{
		if (dup2(current->entry_fd, STDIN_FILENO) == -1)
			return (ft_print_error("dup2 error\n"), -1);
		close(current->entry_fd);
		current->entry_fd = -1;
	}
	else if (prev_pipe_fd != -1 && current->infile_dup == 0)
	{
		if (dup2(prev_pipe_fd, STDIN_FILENO) == -1)
			return (ft_print_error("dup2 error\n"), -1);
		close(prev_pipe_fd);
		prev_pipe_fd = -1;
	}
	return (0);
}
