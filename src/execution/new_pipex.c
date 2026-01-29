/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclouet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:10:10 by tclouet           #+#    #+#             */
/*   Updated: 2025/07/02 17:44:37 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Waits for all child processes to finish and retrieves the last process exit code
 * Handles normal exits and signals appropriately
 */
static void	wait_children(t_shell *shell, pid_t last_pid)
{
	int		status;
	int		last_exit;
	pid_t	pid;

	last_exit = 0;
	while (1)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		else if (pid == last_pid)
		{
			if (WIFEXITED(status))
				last_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_exit = 128 + WTERMSIG(status);
		}
	}
	if (last_exit == 141)
		shell->error = 1;
	else
		shell->error = last_exit;
}

/*
 * Manages the file descriptor from the previous pipe
 * Returns the read end if there's a next command, -1 otherwise
 */
static int	manage_previous_pipe(t_command *current, int *pipe_fd)
{
	if (current->next)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	else
	{
		ft_clean_fd();
		current->entry_fd = -1;
		return (-1);
	}
}

/*
 * Handles input/output redirection for child process in pipeline
 */
static void	child_pro_bloc(t_command *current, int prev_pipe_fd
				, int *pipe_fd, t_shell *shell)
{
	if (ft_manage_entries(shell, current, prev_pipe_fd) == -1)
	{
		ft_free_program(shell);
		exit(1);
	}
	if (ft_manage_exits(current, pipe_fd) == -1)
	{
		ft_free_program(shell);
		exit(1);
	}
}

/*
 * Child process execution - executes command or builtin
 */
static void	child_process(t_command *current, int prev_pipe_fd
				, int *pipe_fd, t_shell *shell)
{
	signal(SIGQUIT, SIG_DFL);
	if (current->args[0] && ft_is_builtin(current->args[0]) != 1)
	{
		child_pro_bloc(current, prev_pipe_fd, pipe_fd, shell);
		ft_exec_cmd(current->args, shell);
	}
	else
	{
		child_pro_bloc(current, prev_pipe_fd, pipe_fd, shell);
		if (ft_is_builtin(current->args[0]) == 1)
			ft_hard_builtin_in_pipe(current, shell);
		ft_free_program(shell);
		exit(shell->error);
	}
}

/*
 * Main pipeline execution function - forks child processes for each command
 * Manages pipes between commands and waits for all children
 */
void	ft_new_pipex(t_shell *shell)
{
	t_command	*current;
	pid_t		pid;
	int			prev_pipe_fd;
	int			pipe_fd[2];

	g_signal = 1;
	prev_pipe_fd = -1;
	current = shell->cmds;
	while (current)
	{
		if (current->next && pipe(pipe_fd) == -1)
			ft_pipex_error(shell, "pipe error");
		pid = fork();
		if (pid == -1)
			ft_pipex_error(shell, "fork error");
		else if (pid == 0)
			child_process(current, prev_pipe_fd, pipe_fd, shell);
		prev_pipe_fd = manage_previous_pipe(current, pipe_fd);
		current = current->next;
	}
	wait_children(shell, pid);
	signal(SIGQUIT, SIG_IGN);
}
