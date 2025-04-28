/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:10:47 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/19 04:06:57 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_specific_expansion(t_expand *exp, char identifier, int is_state)
{
	char	*tmp;

	(void)identifier;
	if (is_state)
		exp->value = ft_itoa(exp->mini->state);
	else
		exp->value = ft_itoa(exp->mini->pid);
	if (!exp->value)
		return (0);
	exp->j = exp->i;
	exp->i += 2;
	tmp = replace_var(exp);
	if (!tmp)
		return (0);
	exp->buffer = tmp;
	exp->i = exp->j + ft_strlen(exp->value);
	free(exp->value);
	return (1);
}

int	handle_pid_expansion(t_expand *exp)
{
	if (exp->buffer[exp->i + 1] == '$')
		return (handle_specific_expansion(exp, '$', 0));
	if (exp->buffer[exp->i + 1] == '?')
		return (handle_specific_expansion(exp, '?', 1));
	return (2);
}

int	process_expansion(t_expand *exp)
{
	int	pid_result;

	if (exp->buffer[exp->i] == '\'')
		return (0);
	if (exp->buffer[exp->i] == '$')
	{
		pid_result = handle_pid_expansion(exp);
		if (pid_result <= 1)
			return (pid_result);
		if (exp->buffer[exp->i + 1] && (ft_isalnum(exp->buffer[exp->i + 1])
				|| exp->buffer[exp->i + 1] == '_'))
		{
			exp->i = process_var(exp);
			return (exp->i != -1 && pars_buff_expand(exp));
		}
		exp->i++;
	}
	else
		exp->i++;
	return (1);
}

int	expand_variables(t_expand *exp)
{
	int	quote_state;

	quote_state = 0;
	while (exp->buffer[exp->i])
	{
		quote_state = handle_quotes(exp->buffer[exp->i], quote_state);
		if (exp->buffer[exp->i] == '$' && quote_state != 1)
		{
			if (!process_expansion(exp))
				return (0);
		}
		else
			exp->i++;
	}
	return (1);
}

int	handle_quotes(char c, int quote_state)
{
	if (c == '\'' && quote_state == 0)
		return (1);
	else if (c == '\'' && quote_state == 1)
		return (0);
	else if (c == '\"' && quote_state == 0)
		return (2);
	else if (c == '\"' && quote_state == 2)
		return (0);
	return (quote_state);
}
