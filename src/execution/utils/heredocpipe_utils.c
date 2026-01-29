/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocpipe_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclouet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:34:37 by tclouet           #+#    #+#             */
/*   Updated: 2025/06/30 09:13:07 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 * Prints bash warning when heredoc ends with EOF instead of delimiter
 */
void	ft_warning_heredoc(char *args)
{
	write(2, "bash: warning: here-document at line 1 delimited ", 49);
	write(2, "by end-of-file (wanted `", 24);
	write(2, args, ft_strlen(args));
	write(2, "')\n", 3);
}

/*
 * Reads heredoc input lines from terminal until delimiter is reached
 * Expands variables if required and writes to pipe
 */
void	ft_read_terminal(t_shell *shell, t_file *current, int tmp_pipe)
{
	char	*line;

	current->delimiter = ft_check_delimiter(shell, current, current->delimiter);
	while (1)
	{
		line = readline((GC "$" EC "> "));
		if (!line || !ft_strcmp(line, current->delimiter))
		{
			if (!line && g_signal != 130)
				ft_warning_heredoc(current->delimiter);
			if (line)
				free(line);
			break ;
		}
		line = ft_check_expand(shell, current, line);
		write(tmp_pipe, line, ft_strlen(line));
		write(tmp_pipe, "\n", 1);
		free(line);
	}
}

/*
 * Signal handler for SIGINT during heredoc input in pipeline
 * Sets error code and displays a new prompt for the terminal
 */
void	handle_signal_heredoc(int sig)
{
	(void)sig;
	g_signal = 130;
	write(STDIN_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	close(STDIN_FILENO);
}

/*
 * Processes heredoc input for a command in a pipeline
 * Creates a pipe and reads heredoc content into it
 * Returns 0 on success, 1 on SIGINT
 */
int	ft_heredoc_mode(t_shell *shell, t_command *current, t_file *infile)
{
	int	heredoc_pipe[2];
	int	saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	if (current->entry_fd != -1)
		close(current->entry_fd);
	if (pipe(heredoc_pipe) == -1)
		ft_print_error("pipe error");
	signal(SIGINT, handle_signal_heredoc);
	ft_read_terminal(shell, infile, heredoc_pipe[1]);
	if (g_signal == 130)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		shell->error = 130;
		return (ft_clean_fd(), 1);
	}
	close(heredoc_pipe[1]);
	current->entry_fd = heredoc_pipe[0];
	return (0);
}

/*
 * Manages heredocs in a pipeline
 * Returns 1 if SIGINT is received, 0 on success
 */
int	ft_manage_heredoc_in_pipe(t_shell *shell)
{
	int			i;
	t_command	*current;

	i = 0;
	current = shell->cmds;
	signal(SIGINT, SIG_IGN);
	while (current)
	{
		i = 0;
		while (i < current->nb_files)
		{
			if (current->files[i].mode == 0
				&& ft_heredoc_mode(shell, current, &current->files[i]))
				return (signal(SIGINT, handle_sig), 1);
			i++;
		}
		current = current->next;
	}
	signal(SIGINT, handle_sig);
	return (0);
}
