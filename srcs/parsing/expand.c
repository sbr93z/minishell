/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:34:11 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/25 16:21:06 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_var_value(char *var, t_env *env_list)
{
	t_env	*current;
	char	*value;

	value = getenv(var);
	if (value)
	{
		if (*value == '\0')
			return ("");
		return (value);
	}
	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, var) == 0)
		{
			if (*(current->content) == '\0')
				return ("");
			return (current->content);
		}
		current = current->next;
	}
	return (NULL);
}

char	*replace_var(t_expand *exp)
{
	char	*new_buffer;
	size_t	prefix_len;
	size_t	value_len;
	size_t	suffix_len;
	size_t	total_len;

	prefix_len = exp->j;
	value_len = ft_strlen(exp->value);
	suffix_len = ft_strlen(exp->buffer + exp->i);
	total_len = prefix_len + value_len + suffix_len + 1;
	new_buffer = gc_malloc(total_len, exp->gc);
	if (!new_buffer)
		return (NULL);
	if (prefix_len > 0)
		ft_strlcpy(new_buffer, exp->buffer, prefix_len + 1);
	else
		new_buffer[0] = '\0';
	ft_strlcat(new_buffer, exp->value, total_len);
	ft_strlcat(new_buffer, exp->buffer + exp->i, total_len);
	return (new_buffer);
}

int	process_var(t_expand *exp)
{
	char	*tmp_buffer;
	int		var_start;
	int		var_len;

	var_start = exp->i + 1;
	exp->i = var_start;
	while (exp->buffer[exp->i] && (ft_isalnum(exp->buffer[exp->i])
			|| exp->buffer[exp->i] == '_'))
		exp->i++;
	var_len = exp->i - var_start;
	if (var_len == 0)
		return (var_start);
	exp->var = gc_malloc(var_len + 1, exp->gc);
	if (!exp->var)
		return (-1);
	ft_strlcpy(exp->var, exp->buffer + var_start, var_len + 1);
	exp->value = get_var_value(exp->var, exp->mini->env_list);
	if (!exp->value)
		exp->value = "";
	exp->j = var_start - 1;
	tmp_buffer = replace_var(exp);
	if (!tmp_buffer)
		return (-1);
	exp->buffer = tmp_buffer;
	return (exp->j + ft_strlen(exp->value));
}

int	pars_buff_expand(t_expand *exp)
{
	int	j;

	j = exp->j;
	while (j < exp->i)
	{
		if (exp->buffer[j] == '\'' || exp->buffer[j] == '>'
			|| exp->buffer[j] == '\"' || exp->buffer[j] == '|'
			|| exp->buffer[j] == '<' || exp->buffer[j] == '.')
			exp->buffer[j] = exp->buffer[j] * -1;
		j++;
	}
	exp->j = j;
	return (1);
}

char	*expand_vars(char *buffer, t_mini *mini, t_gc_list *gc)
{
	t_expand	exp;
	char		*tmp;

	tmp = gc_strdup(buffer, gc);
	if (!tmp)
		return (NULL);
	exp.buffer = tmp;
	exp.mini = mini;
	exp.gc = gc;
	exp.i = 0;
	exp.is_pid = 0;
	if (!expand_variables(&exp))
		return (NULL);
	return (exp.buffer);
}
