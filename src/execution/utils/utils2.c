/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclouet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:04:46 by tclouet           #+#    #+#             */
/*   Updated: 2025/07/02 17:44:59 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 * Handles errors in pipeline execution - prints error and exits
 */
void	ft_pipex_error(t_shell *shell, char *message)
{
	write(2, "bash: ", 6);
	perror(message);
	if (errno == EMFILE || errno == ENFILE)
		shell->error = 2;
	else
		shell->error = 1;
	ft_free_program(shell);
	exit(shell->error);
}

/*
 * Custom strchr variant - returns 1 if character found, 0 otherwise
 */
int	ft_new_strchr(char *s, int c)
{
	while (*s != (unsigned char) c)
	{
		if (*s == 0)
			return (0);
		s++;
	}
	return (1);
}

/*
 * Manages input/output redirections for commands without pipe
 */
void	ft_manage_redirections(t_shell *shell)
{
	int			i;
	t_command	*current;

	i = 0;
	current = shell->cmds;
	while (i < current->nb_files)
	{
		if (current->files[i].mode == 1)
		{
			if (ft_check_infile(shell, current->files[i].file) == -1)
				break ;
		}
		else if (current->files[i].mode == 2 || current->files[i].mode == 3)
		{
			if (ft_outfile_mode_no_pipe(shell, current->files[i].file,
					current->files[i].mode) == -1)
				break ;
		}
		i++;
	}
}
