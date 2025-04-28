/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:13:04 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/25 16:46:26 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	handle_argument(t_token **token, t_command *cmd, t_mini *shell)
{
	cmd->arguments = add_argument(cmd->arguments, expand((*token)->arg, shell),
			shell->gc);
	if (!cmd->arguments)
		return (printf("Erreur"), 0);
	(*token) = (*token)->next;
	return (1);
}

bool	is_argument_token(t_token *token)
{
	return (token->type == STRING || token->type == CMD
		|| token->type == BUILTIN);
}

int	handle_syntax_error(char *buffer, int *i)
{
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("bash: syntax error near ", 2);
	if (!buffer[*i])
		ft_putstr_fd("unexpected token `newline'\n", 2);
	else
	{
		ft_putstr_fd("unexpected token `", 2);
		ft_putchar_fd(buffer[*i], 2);
		ft_putstr_fd("'\n", 2);
	}
	return (0);
}

int	handle_pipe_error(void)
{
	ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	return (0);
}
