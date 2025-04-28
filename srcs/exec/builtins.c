/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:16:23 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/25 00:51:04 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_builtins(t_mini *shell, char **arg, t_gc_list *gc)
{
	if (!arg || !arg[0])
		return (1);
	if (ft_strcmp(arg[0], "env") == 0)
		return (printf_env(shell->env_list, shell));
	else if (ft_strcmp(arg[0], "export") == 0)
		return (cmd_export(arg, &(shell->env_list), shell));
	else if (ft_strcmp(arg[0], "exit") == 0)
		return (ft_exit(arg, gc, shell));
	else if (ft_strcmp(arg[0], "unset") == 0)
		return (ft_unset(&(shell->env_list), arg[1], shell));
	else if (ft_strcmp(arg[0], "cd") == 0)
		return (ft_cd(&(shell->env_list), arg[1], shell->gc, shell));
	else if (ft_strcmp(arg[0], "pwd") == 0)
		return (ft_pwd(shell));
	else if (ft_strcmp(arg[0], "echo") == 0)
		return (ft_echo(&(shell->env_list), arg, shell));
	return (1);
}

int	builtins(t_mini *shell, t_command *cmd, t_gc_list *gc)
{
	int	save[2];
	int	status;

	save[STDIN_FILENO] = dup(STDIN_FILENO);
	save[STDOUT_FILENO] = dup(STDOUT_FILENO);
	open_redirections(cmd, shell);
	if (ft_strcmp("exit", cmd->arguments[0]) == 0)
	{
		dup2(save[STDIN_FILENO], STDIN_FILENO);
		dup2(save[STDOUT_FILENO], STDOUT_FILENO);
		(close(save[0]), close(save[1]));
		free_all_heredoc(shell->command);
		return (ft_exit(cmd->arguments, gc, shell));
	}
	status = exec_builtins((t_mini *)shell, cmd->arguments, gc);
	dup2(save[STDIN_FILENO], STDIN_FILENO);
	dup2(save[STDOUT_FILENO], STDOUT_FILENO);
	(close(save[0]), close(save[1]));
	free_all_heredoc(shell->command);
	return (status);
}
