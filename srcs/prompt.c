/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:55:50 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/29 11:55:24 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_command(t_token *token, t_mini *shell, t_gc_list *gc)
{
	char	**args;
	char	**cmd;
	pid_t	pid;
	int		arg_count;

	args = extract_args_from_token(token, &arg_count, gc);
	if (!args)
		return (0);
	pid = fork();
	if (pid == 0)
	{
		cmd = prepare_command_and_get_path(token->arg, shell, gc);
		if (cmd)
		{
			execve(cmd[0], args, shell->envp);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		return (ft_putstr_fd("Fork Error\n", 2), 0);
	return (1);
}

int	execute_token(t_token *token, t_mini *shell, t_gc_list *gc)
{
	char	**args;
	int		arg_count;
	t_token	*cat_token;

	if (token->type == REDIRECT && (!token->next || token->next->type == PIPE))
	{
		cat_token = ft_lstnew_mini(gc_strdup("cat", gc), CMD, gc);
		execute_command(cat_token, shell, gc);
		return (1);
	}
	if (token->type == BUILTIN)
	{
		args = extract_args(token, &arg_count, gc);
		if (!args)
			return (1);
		return (exec_builtins((t_mini *)shell, args, gc));
	}
	if (token->type == CMD)
		return (execute_command(token, shell, gc));
	return (1);
}

int	execute_tokens(t_token *token_list, t_mini *shell, t_gc_list *gc)
{
	t_token	*current_token;

	current_token = token_list;
	while (current_token)
	{
		if (current_token->type == BUILTIN || current_token->type == CMD)
		{
			if (!execute_token(current_token, shell, gc))
				break ;
			while (current_token->next && current_token->next->type == STRING)
				current_token = current_token->next;
		}
		else
		{
			if (!execute_token(current_token, shell, gc))
				break ;
		}
		current_token = current_token->next;
	}
	return (1);
}

int	process_command(t_mini *shell, t_gc_list *gc)
{
	t_token	*token_list;

	shell->gc = gc;
	token_list = parsing(shell->buffer, shell, gc);
	if (!token_list)
		return (0);
	restore_tokens(token_list);
	shell->token_list = token_list;
	if (!tidying(shell))
		return (0);
	shell->token_list = token_list;
	if (!shell->command)
		return (0);
	exec(shell->command, shell, gc);
	ft_commandclear(&shell->command);
	return (1);
}

int	ft_prompt(char **envp)
{
	t_mini		shell;
	t_env		*env_list;
	t_gc_list	gc;

	gc.head = NULL;
	ft_memset(&shell, 0, sizeof(t_mini));
	env_list = init_env(envp, &gc);
	if (!env_list)
		return (EXIT_FAILURE);
	init_states(&shell, envp);
	shell.env_list = env_list;
	if (process_input(&shell, &gc))
	{
		cleanup_states(&shell);
		free_env_list(env_list);
		return (gc_free_all(&gc), 0);
	}
	rl_clear_history();
	cleanup_states(&shell);
	free_env_list(env_list);
	return (gc_free_all(&gc), 0);
}
