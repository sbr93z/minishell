/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:32:47 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/25 02:01:13 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*ft_commandnew(char **tabl, t_redir *redir, t_gc_list *gc)
{
	t_command	*cmd;

	(void)gc;
	cmd = gc_malloc(sizeof(t_command), gc);
	if (!cmd)
		return (NULL);
	cmd->arguments = tabl;
	cmd->redir = redir;
	cmd->next = NULL;
	cmd->pid = 0;
	return (cmd);
}

t_command	*ft_commandlast(t_command *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_commandaddback(t_command **head, t_command *new)
{
	if (!head)
		return ;
	if (*head)
		ft_commandlast(*head)->next = new;
	else
		*head = new;
}

t_command	*init_command_struct(t_token *token_start, t_gc_list *gc)
{
	t_command	*cmd;
	int			arg_count;

	arg_count = count_command_args(token_start);
	cmd = gc_malloc(sizeof(t_command), gc);
	if (!cmd)
		return (NULL);
	cmd->arguments = gc_malloc(sizeof(char *) * (arg_count + 1), gc);
	if (!cmd->arguments)
		return (NULL);
	cmd->redir = NULL;
	cmd->next = NULL;
	cmd->pid = 0;
	return (cmd);
}
