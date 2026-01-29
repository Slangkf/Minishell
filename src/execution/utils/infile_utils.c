/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclouet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:29:17 by tclouet           #+#    #+#             */
/*   Updated: 2025/06/17 10:30:37 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 * Checks if an input file exists and can be read
 * Returns file descriptor on success, -1 and prints error if not found
 */
int	ft_check_infile(t_shell *shell, char *infile)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
	{
		write(2, "bash: ", 6);
		write(2, infile, ft_strlen(infile));
		write(2, ": No such file or directory\n", 28);
		shell->error = 1;
	}
	return (infile_fd);
}
