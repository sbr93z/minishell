/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:55:08 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/25 16:24:49 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_redirections(t_token *token_start, t_command *cmd, t_gc_list *gc,
		t_mini *shell)
{
	t_token	*temp_ptr;
	t_token	*redirect_token;

	temp_ptr = token_start;
	redirect_token = NULL;
	while (temp_ptr && temp_ptr->type != PIPE)
	{
		if (temp_ptr->type == REDIRECT)
		{
			redirect_token = temp_ptr;
			handle_redirection(&redirect_token, cmd, gc, shell);
			temp_ptr = redirect_token;
		}
		else
			temp_ptr = temp_ptr->next;
	}
}

static void	fill_arguments_loop(t_command *cmd, t_token *temp_ptr, int *i,
		int *cmd_found)
{
	while (temp_ptr && temp_ptr->type != PIPE)
	{
		if (temp_ptr->type == CMD || temp_ptr->type == BUILTIN)
		{
			cmd->arguments[(*i)++] = temp_ptr->arg;
			*cmd_found = 1;
		}
		else if (temp_ptr->type == STRING)
		{
			cmd->arguments[(*i)++] = temp_ptr->arg;
		}
		else if (temp_ptr->type == REDIRECT)
		{
			temp_ptr = temp_ptr->next;
			if (temp_ptr)
				temp_ptr = temp_ptr->next;
			continue ;
		}
		if (temp_ptr)
			temp_ptr = temp_ptr->next;
	}
}

void	fill_command_arguments(t_command *cmd, t_token *token_start,
		t_gc_list *gc)
{
	int		i;
	int		cmd_found;
	t_token	*temp_ptr;

	i = 0;
	cmd_found = 0;
	temp_ptr = token_start;
	if (temp_ptr && temp_ptr->type == REDIRECT)
		cmd_found = 1;
	fill_arguments_loop(cmd, temp_ptr, &i, &cmd_found);
	if (!cmd_found && i == 0)
		cmd->arguments[i++] = gc_strdup("cat", gc);
	cmd->arguments[i] = NULL;
}

static void	setup_command_info(t_command *cmd, t_token *start, t_gc_list *gc,
		t_mini *shell)
{
	t_token	*temp;
	int		has_command;

	has_command = 0;
	temp = start;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == CMD || temp->type == BUILTIN)
		{
			has_command = 1;
			break ;
		}
		temp = temp->next;
	}
	if (!has_command && cmd->arguments)
		cmd->arguments[0] = gc_strdup("cat", gc);
	handle_redirections(start, cmd, gc, shell);
	fill_command_arguments(cmd, start, gc);
}

t_command	*create_single_command(t_token **token_ptr, t_gc_list *gc,
		t_mini *shell)
{
	t_command	*cmd;
	t_token		*token_start;

	token_start = *token_ptr;
	if (!token_start)
		return (NULL);
	cmd = init_command_struct(token_start, gc);
	if (!cmd)
		return (NULL);
	setup_command_info(cmd, token_start, gc, shell);
	while (*token_ptr && (*token_ptr)->type != PIPE)
		*token_ptr = (*token_ptr)->next;
	return (cmd);
}
