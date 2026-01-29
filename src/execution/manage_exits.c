/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_exits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclouet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:00:07 by tclouet           #+#    #+#             */
/*   Updated: 2025/06/17 11:04:06 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Opens an output file in truncate (>) or append (>>) mode
 * Redirects STDOUT if it's the last output redirection
 * Returns 0 on success, -1 on error
 */
int	ft_outfile_mode(t_command *curr, t_file *outfile, int append_mode)
{
	int	outfile_fd;

	outfile_fd = -1;
	if (append_mode == 2)
	{
		outfile_fd = open(outfile->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd == -1)
			return (ft_print_error(outfile->file), -1);
	}
	else if (append_mode == 3)
	{
		outfile_fd = open(outfile->file, O_WRONLY | O_CREAT
				| O_APPEND, 0644);
		if (outfile_fd == -1)
			return (ft_print_error(outfile->file), -1);
	}
	if (outfile->f_last_out == 1)
	{
		if (dup2(outfile_fd, STDOUT_FILENO) == -1)
			return (ft_print_error("dup2 error\n"), -1);
		curr->outfile_dup = 1;
	}
	close(outfile_fd);
	return (0);
}

/*
 * Manages output redirection for a command (pipe or STDOUT)
 * Returns 0 on success, -1 on error
 */
int	ft_manage_exits(t_command *current, int *pipe_fd)
{
	if (current->next && current->outfile_dup == 0)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			return (ft_print_error("dup2 error\n"), -1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	return (0);
}
