/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclouet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:06:15 by tclouet           #+#    #+#             */
/*   Updated: 2025/06/14 11:06:17 by tclouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 * Opens an output file in truncate (>) or append (>>) mode (no pipe case)
 * Returns 0 on success, -1 if file cannot be created
 */
int	ft_outfile_mode_no_pipe(t_shell *shell, char *outfile, int append_mode)
{
	int	outfile_fd;

	outfile_fd = 0;
	if (append_mode == 2)
	{
		outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd == -1)
		{
			shell->error = 1;
			return (ft_print_error(outfile), -1);
		}
	}
	else if (append_mode == 3)
	{
		outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile_fd == -1)
		{
			shell->error = 1;
			return (ft_print_error(outfile), -1);
		}
	}
	close(outfile_fd);
	return (0);
}
