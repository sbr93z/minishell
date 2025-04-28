/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:42:11 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/25 16:23:33 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_command_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == CMD || token->type == BUILTIN
			|| token->type == STRING)
			count++;
		token = token->next;
	}
	return (count);
}

static void	help_redirection(t_redir *new_redir)
{
	new_redir->type = HEREDOC;
}

void	handle_redirection(t_token **token_ptr, t_command *cmd, t_gc_list *gc,
		t_mini *shell)
{
	t_redir	*new_redir;

	(void)shell;
	new_redir = gc_malloc(sizeof(t_redir), gc);
	if (!new_redir)
		return ;
	if (ft_strcmp((*token_ptr)->arg, ">") == 0)
		new_redir->type = OUT;
	else if (ft_strcmp((*token_ptr)->arg, ">>") == 0)
		new_redir->type = APPEND;
	else if (ft_strcmp((*token_ptr)->arg, "<") == 0)
		new_redir->type = IN;
	else if (ft_strcmp((*token_ptr)->arg, "<<") == 0)
		help_redirection(new_redir);
	*token_ptr = (*token_ptr)->next;
	if (*token_ptr && (*token_ptr)->type == STRING)
	{
		new_redir->file = (*token_ptr)->arg;
		if (new_redir->type == HEREDOC)
			get_heredoc(new_redir, shell);
	}
	else
		return ;
	new_redir->next = cmd->redir;
	cmd->redir = new_redir;
}

t_command	*create_command_list(t_token *token_list, t_gc_list *gc,
		t_mini *shell)
{
	t_command	*command_list;
	t_command	*current_command;
	t_command	*new_command;
	t_token		*current_token;

	command_list = NULL;
	current_command = NULL;
	current_token = token_list;
	while (current_token)
	{
		if (current_token->type == PIPE)
		{
			current_token = current_token->next;
			continue ;
		}
		new_command = create_single_command(&current_token, gc, shell);
		if (!new_command)
			return (NULL);
		if (!command_list)
			command_list = new_command;
		else
			current_command->next = new_command;
		current_command = new_command;
	}
	return (command_list);
}
