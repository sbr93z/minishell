/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:30:30 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/25 16:22:32 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_cmd(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->arguments)
	{
		i = 0;
		while (cmd->arguments[i])
		{
			free(cmd->arguments[i]);
			i++;
		}
		free(cmd->arguments);
	}
	ft_redirclear(cmd->redir);
	free(cmd);
}

bool	tidying(t_mini *shell)
{
	t_token		*token;
	t_command	*cmd;

	token = shell->token_list;
	while (token)
	{
		cmd = ft_commandnew(NULL, NULL, shell->gc);
		if (!cmd)
			return (ft_commandclear(&shell->command), 0);
		while (token && token->type != PIPE)
		{
			if (!handle_token(&token, cmd, shell))
			{
				free_tab(cmd->arguments);
				ft_redirclear(cmd->redir);
				free(cmd);
				return (0);
			}
		}
		ft_commandaddback(&(shell->command), cmd);
		if (!token)
			break ;
		token = token->next;
	}
	return (1);
}
