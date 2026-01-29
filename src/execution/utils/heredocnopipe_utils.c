/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocnopipe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclouet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:25:11 by tclouet           #+#    #+#             */
/*   Updated: 2025/07/03 11:42:45 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 * Signal handler for SIGINT during heredoc input (no pipe case)
 * Sets error code and displays a new prompt for the terminal
 */
void	handle_signal_heredoc_no_pipe(int sig)
{
	(void)sig;
	g_signal = 130;
	write(STDIN_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	close(STDIN_FILENO);
}

/*
 * Processes heredoc input for commands without pipe
 * Forks a child process to read heredoc lines
 */
void	ft_heredoc_mode_no_pipe(t_file *current, t_shell *shell)
{
	int		heredoc_pipe[2];
	int		status;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	if (pipe(heredoc_pipe) == -1)
		ft_print_error("pipe error");
	pid = fork();
	if (pid == -1)
		ft_print_error("fork error");
	else if (pid == 0)
	{
		signal(SIGINT, handle_signal_heredoc_no_pipe);
		ft_read_terminal(shell, current, heredoc_pipe[1]);
		ft_clean_fd();
		ft_free_program(shell);
		exit (g_signal);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->error = WEXITSTATUS(status);
	else
		shell->error = 130;
	ft_clean_fd();
	signal(SIGINT, handle_sig);
}

/*
 * Manages heredocs without pipeline
 * Processes each file redirection in order
 */
void	ft_manage_heredoc_no_pipe(t_shell *shell)
{
	int			i;
	t_command	*current;

	i = 0;
	current = shell->cmds;
	while (i < current->nb_files)
	{
		if (current->files[i].mode == 0)
			ft_heredoc_mode_no_pipe(&current->files[i], shell);
		{
			if (shell->error == 130)
				return ;
		}
		i++;
	}
}
