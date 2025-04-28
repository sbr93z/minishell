/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opens.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:09:37 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/17 20:50:49 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	open_output(t_redir *redir, t_mini *shell)
{
	int	fd;

	(void)shell;
	if (redir->type == OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->type == APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(redir->file);
		gc_free_all(shell->gc);
		free_env_list(shell->env_list);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static int	create_heredoc_pipe(int fd[2], t_mini *shell)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		shell->state = 1;
		return (0);
	}
	return (1);
}

void	open_heredoc(t_redir *redir, t_mini *shell)
{
	int	i;
	int	fd[2];

	if (!redir || !redir->heredoc_content)
		return ;
	if (!create_heredoc_pipe(fd, shell))
		return ;
	i = 0;
	while (redir->heredoc_content && redir->heredoc_content[i])
		ft_putendl_fd(redir->heredoc_content[i++], fd[1]);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd[0]);
		shell->state = 1;
		return ;
	}
	close(fd[0]);
}

int	open_redirections(t_command *cmd, t_mini *shell)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == IN)
			open_input(redir, shell);
		else if (redir->type == OUT)
			open_output(redir, shell);
		else if (redir->type == APPEND)
			open_output(redir, shell);
		else if (redir->type == HEREDOC)
			open_heredoc(redir, shell);
		redir = redir->next;
	}
	return (1);
}

void	open_input(t_redir *redir, t_mini *shell)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->file);
		gc_free_all(shell->gc);
		free_env_list(shell->env_list);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
