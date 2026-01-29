/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:04:01 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 10:52:30 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Implement of the action for CTRL+C
 * Send information to the global that a CTRL+C been executed
 * Replace and re prompt the readline line
 */
void	handle_sig(int sig)
{
	int		ret;

	(void)sig;
	ret = g_signal;
	g_signal = 130;
	write(STDIN_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (ret == 0 || ret == 130)
		rl_redisplay();
}

/*
 * Initialise CTRL+C and CTRL+\
 * ^C Should be send into handle_sig()
 * ^\ Should be ignored as desired in interactive mode
 * Exit if the function sigaction() failed
 */
void	signal_received(void)
{
	struct sigaction	sa_c;
	struct sigaction	sa_slash;

	ft_bzero(&sa_c, sizeof(sigaction));
	ft_bzero(&sa_slash, sizeof(sigaction));
	sa_slash.sa_handler = SIG_IGN;
	sigemptyset(&sa_slash.sa_mask);
	sa_slash.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_slash, NULL) == -1)
	{
		write(2, "sigaction failed\n", 17);
		exit(EXIT_FAILURE);
	}
	sa_c.sa_handler = handle_sig;
	sigemptyset(&sa_c.sa_mask);
	sa_c.sa_flags = 0;
	if (sigaction(SIGINT, &sa_c, NULL) == -1)
	{
		write(2, "sigaction failed\n", 17);
		exit(EXIT_FAILURE);
	}
}
