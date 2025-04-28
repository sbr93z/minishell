/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:21:31 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/25 16:21:29 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	get_expanded_len(char *str, t_mini *shell)
{
	int	len;
	int	i;
	int	quote_index;

	len = 0;
	i = 0;
	quote_index = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quote_index != 2)
			quote_index = change_quote(str[i++], quote_index);
		else if (str[i] == '"' && quote_index != 1)
			quote_index = change_quote(str[i++], quote_index);
		else
		{
			if (str[i] == '$' && quote_index != 1)
				len += get_env_size(str, &i, shell);
			else
			{
				i++;
				len++;
			}
		}
	}
	return (len);
}

void	if_expand(t_mini *shell, char *expanded, int *i)
{
	char	*st;

	st = NULL;
	st = ft_itoa(shell->state);
	if (!st)
	{
		ft_end(shell);
		exit(EXIT_FAILURE);
	}
	*i += 2;
	ft_strncat(expanded, st, ft_strlen(st));
	free(st);
}

char	*while_expand(char *str, char *expanded, t_mini *shell)
{
	int	i;
	int	quote_index;

	i = 0;
	quote_index = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quote_index != 2)
			quote_index = change_quote(str[i++], quote_index);
		else if (str[i] == '"' && quote_index != 1)
			quote_index = change_quote(str[i++], quote_index);
		else
		{
			if (str[i] == '$' && quote_index != 1)
				get_env_value(str, expanded, &i, shell);
			else
				ft_strncat(expanded, str + i++, 1);
		}
	}
	return (expanded);
}

char	*expand(char *str, t_mini *shell)
{
	char	*expanded;
	int		len;

	len = get_expanded_len(str, shell);
	expanded = gc_malloc(len + 1, shell->gc);
	if (!expanded)
		return (NULL);
	ft_memset(expanded, 0, len + 1);
	expanded = while_expand(str, expanded, shell);
	return (expanded);
}
