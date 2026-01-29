/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:04:53 by seruff            #+#    #+#             */
/*   Updated: 2025/07/01 14:35:22 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Checks if a file path is valid and accessible
 * Handles errors: permission denied (126) or file not found (127)
 * Returns 0 if valid, 1 if permission denied, 2 if not found
 */
int	check_file(char *s, t_shell *shell)
{
	if (chdir(s) == -1)
	{
		if (errno == EACCES || errno == ENOTDIR)
		{
			shell->error = 126;
			write(2, "bash : ", 7);
			write(2, s, ft_strlen(s));
			write(2, ": Permission denied\n", 20);
			return (1);
		}
		else if (errno == ENOENT)
		{
			shell->error = 127;
			return (ft_no_file_or_directory(s), 2);
		}
	}
	else if (ft_strchr(s, '/'))
	{
		shell->error = 126;
		write(2, "bash : ", 7);
		write(2, s, ft_strlen(s));
		write(2, ": Is a directory\n", 17);
		return (1);
	}
	return (0);
}
