/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:16:08 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 10:43:49 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	file_exist(char *file)
{
	struct stat	buffer;

	return (stat(file, &buffer) == 0);
}

/*
 * String contains only digits
 */
int	ft_string_digit(char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (-1);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

/*
 * Handle and display error cases
 * Directory without access
 * Directory that doesn't exist
 */
int	cd_fails(char *temp, char *arg, int ret)
{
	if (ret == -1 && check_directory_access(arg) == 0)
	{
		write(2, "bash: cd: ", 10);
		perror(arg);
		free(temp);
		return (1);
	}
	else if (ret == -1 && check_directory_access(arg) == 2)
	{
		write(2, "bash: cd: ", 10);
		write(2, arg, ft_strlen(arg));
		write(2, ": Not a directory\n", 18);
		free(temp);
		return (1);
	}
	return (0);
}

/*
 * Display error message
 */
void	print_error_cd(t_shell *shell, char *s, int type)
{
	if (type == 1)
	{
		write(2, "bash: cd: HOME not set\n", 23);
		shell->error = 1;
	}
	else if (type == 2)
	{
		write(2, "bash: cd: too many arguments\n", 29);
		shell->error = 1;
	}
	else if (type == 3)
	{
		shell->error = 1;
		write(2, "bash: cd: ", 10);
		write(2, s, ft_strlen(s));
		write(2, ": No such file or directory\n", 28);
	}
	else if (type == 4)
	{
		shell->error = 1;
		write(2, "bash: cd: ", 10);
		write(2, s, ft_strlen(s));
		write(2, ": Not a directory\n", 18);
	}
}
