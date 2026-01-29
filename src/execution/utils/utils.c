/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclouet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:16:11 by tclouet           #+#    #+#             */
/*   Updated: 2025/06/14 11:03:41 by tclouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 * Prints a bash-style error message with perror
 */
void	ft_print_error(char *message)
{
	write(2, "bash: ", 6);
	perror(message);
}

/*
 * Prints command not found error message
 */
void	ft_cmd_not_found(char *arg)
{
	write(2, "bash: ", 6);
	write(2, arg, ft_strlen(arg));
	write(2, ": command not found\n", 20);
}

/*
 * Prints file or directory not found error message
 */
void	ft_no_file_or_directory(char *arg)
{
	write(2, "bash: ", 6);
	write(2, arg, ft_strlen(arg));
	write(2, ": No such file or directory\n", 28);
}

/*
 * Frees a NULL-terminated array of strings
 */
void	ft_free_all(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
}

/*
 * Closes all open file descriptors
 */
void	ft_clean_fd(void)
{
	int	i;

	i = 3;
	while (i <= 1023)
	{
		if (close(i++) == -1)
		{
			if (close(i++) == -1)
				break ;
		}
	}
}
