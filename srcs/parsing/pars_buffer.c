/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:56:25 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/17 20:55:57 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quote(char *buffer, int *i)
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

int	check_redir_syntax(char *buffer, int *i)
{
	char	current;
	char	next;
	int		has_next_arg;

	current = buffer[*i];
	next = buffer[*i + 1];
	if ((current == '>' || current == '<'))
	{
		if ((current == '>' && next == '>') || (current == '<' && next == '<'))
			(*i)++;
		(*i)++;
		while (buffer[*i] && (buffer[*i] == ' ' || buffer[*i] == '\t'))
			(*i)++;
		has_next_arg = (buffer[*i] && buffer[*i] != '>' && buffer[*i] != '<'
				&& buffer[*i] != '|');
		if (!has_next_arg)
			return (handle_syntax_error(buffer, i));
	}
	return (1);
}

int	check_pipe_syntax(char *buffer, int *i)
{
	if (buffer[*i] == '|')
	{
		(*i)++;
		while (buffer[*i] && (buffer[*i] == ' ' || buffer[*i] == '\t'))
			(*i)++;
		if (!buffer[*i])
			return (handle_syntax_error(buffer, i));
		if (buffer[*i] == '|')
			return (handle_pipe_error_buff());
	}
	return (1);
}

int	check_redirections(char *buffer, int *i)
{
	if (!buffer[*i])
		return (1);
	if (!check_redir_syntax(buffer, i))
		return (0);
	if (!check_pipe_syntax(buffer, i))
		return (0);
	return (1);
}

int	pars_buff(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] == ' ' || buffer[i] == '\t')
		i++;
	if (buffer[i] == '|')
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2), 0);
	if (!check_redirections(buffer, &i))
		return (0);
	while (buffer[i])
	{
		if (buffer[i] == '"' || buffer[i] == '\'')
		{
			if (!check_quote(buffer, &i))
				return (0);
		}
		if (buffer[i] == '|' || buffer[i] == '>' || buffer[i] == '<')
		{
			if (!check_redirections(buffer, &i))
				return (0);
		}
		i++;
	}
	return (1);
}
