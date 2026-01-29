/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:24:19 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 10:39:26 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Error message of the exit command
 */
void	print_exit(int type, char *s)
{
	if (type == 1)
	{
		write(2, "bash: exit: ", 12);
		write(2, s, ft_strlen(s));
		write(2, ": numeric argument required\n", 28);
	}
	else if (type == 2)
		write(2, "bash: exit: too many arguments\n", 31);
}

/*
 * Verification of the right input for the argument of exit cmd
 * Need to be a digit only between 0 to 255 as an unsigned int n
 */
int	ft_str_digit(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_numeric(t_shell *shell, char *s)
{
	if (ft_str_digit(s) == 1)
	{
		shell->error = 2;
		return (1);
	}
	if (ft_atoll(s) == -1)
		return (2);
	return (0);
}

/*
 * Exit command bloc to exit() the program 
 * properly with an argument if given
 * Otherwise return 0
 * Or return -2 if any wrong args like "hello" or 2 args
 */
void	exit_cmd(t_shell *shell, char **args)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (!args[1])
		shell->error = shell->error;
	else if (is_numeric(shell, args[1]) == 1)
		print_exit(1, args[1]);
	else if (args[2])
	{
		print_exit(2, NULL);
		shell->error = 1;
		return ;
	}
	else if (is_numeric(shell, args[1]) == 2)
		shell->error = -2;
	else
		shell->error = ft_atoll(args[1]);
	ft_free_program(shell);
	exit(shell->error);
}

/*
 * Exit with CTRL+D (impact with readline who send EOF and return NULL
 */
int	exit_ctrld(t_shell *shell)
{
	(void)shell;
	write(STDIN_FILENO, "exit\n", 5);
	ft_clean_fd();
	exit(0);
}
