/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_buffer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:00:00 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/17 20:56:03 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quotes(char *buffer, int *i)
{
	char	quote;

	quote = buffer[*i];
	(*i)++;
	while (buffer[*i] && buffer[*i] != quote)
		(*i)++;
	if (!buffer[*i])
	{
		ft_putstr_fd("syntax error: unclosed quote\n", 2);
		return (0);
	}
	return (1);
}

int	handle_syntax_error_buff(char *buffer, int *i)
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

int	handle_pipe_error_buff(void)
{
	ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	return (0);
}

int	check_pipe(char *buffer, int *i)
{
	int	consecutive_pipes;

	consecutive_pipes = 0;
	while (buffer[*i + consecutive_pipes] == '|')
		consecutive_pipes++;
	if (consecutive_pipes > 1)
	{
		ft_putstr_fd("syntax error near unexpected token `||'\n", 2);
		return (0);
	}
	(*i)++;
	while (buffer[*i] && (buffer[*i] == ' ' || buffer[*i] == '\t'))
		(*i)++;
	if (!buffer[*i])
		return (handle_syntax_error_buff(buffer, i));
	return (1);
}

int	check_redir(char *buffer, int *i)
{
	char	current;
	char	next;

	current = buffer[*i];
	next = buffer[*i + 1];
	if ((current == '>' && next == '>') || (current == '<' && next == '<'))
		(*i)++;
	(*i)++;
	while (buffer[*i] && (buffer[*i] == ' ' || buffer[*i] == '\t'))
		(*i)++;
	if (!buffer[*i] || buffer[*i] == '>' || buffer[*i] == '<'
		|| buffer[*i] == '|')
		return (handle_syntax_error_buff(buffer, i));
	return (1);
}
