/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:50:00 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/25 16:21:22 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execut_me(t_command *cmd, t_mini *shell, int save[2], int fd[2])
{
	int	status;

	set_signal_child();
	if (cmd->next)
		dup2(fd[1], STDOUT_FILENO);
	(close(save[0]), close(save[1]));
	open_redirections(cmd, shell);
	(close(fd[0]), close(fd[1]));
	if (cmd->arguments == NULL || cmd->arguments[0] == NULL)
	{
		gc_free_all(shell->gc);
		free_env_list(shell->env_list);
		exit(EXIT_SUCCESS);
	}
	if (is_builtin(cmd->arguments))
	{
		status = builtins(shell, cmd, shell->gc);
		free_env_list(shell->env_list);
		gc_free_all(shell->gc);
		exit(status);
	}
	ft_tabupdate(shell);
	excute(cmd->arguments, shell->envp, shell);
}

int	all_cmd(t_mini *minishell, int save[2], t_command *cmd)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (close(fd[0]), close(fd[1]), -1);
	if (cmd->pid == 0)
		execut_me(cmd, minishell, save, fd);
	dup2(fd[0], STDIN_FILENO);
	(close(fd[0]), close(fd[1]));
	return (1);
}

void	check_signal_exec(t_mini *minishell)
{
	if (minishell->state == 128 + SIGINT)
		printf("\n");
	else if (minishell->state == 128 + SIGQUIT)
		printf("Quit (core dumped)\n");
}

void	waiter(t_command *cmd, t_mini *minishell)
{
	while (cmd)
	{
		waitpid(cmd->pid, &minishell->state, 0);
		if (WIFEXITED(minishell->state))
			minishell->state = WEXITSTATUS(minishell->state);
		else if (WIFSIGNALED(minishell->state))
			minishell->state = 128 + WTERMSIG(minishell->state);
		else if (WIFSTOPPED(minishell->state))
			minishell->state = 128 + WSTOPSIG(minishell->state);
		cmd = cmd->next;
	}
}

bool	exec(t_command *cmd, t_mini *shell, t_gc_list *gc)
{
	int	save[2];

	if (!cmd || !shell)
		return (false);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	shell->gc = gc;
	if (!cmd->next && is_builtin(cmd->arguments))
		return (builtins(shell, cmd, gc), 1);
	save[STDIN_FILENO] = dup(STDIN_FILENO);
	save[STDOUT_FILENO] = dup(STDOUT_FILENO);
	while (cmd)
	{
		all_cmd(shell, save, cmd);
		cmd = cmd->next;
	}
	cmd = shell->command;
	waiter(cmd, shell);
	dup2(save[STDIN_FILENO], STDIN_FILENO);
	dup2(save[STDOUT_FILENO], STDOUT_FILENO);
	(close(save[0]), close(save[1]));
	check_signal_exec(shell);
	return (0);
}
