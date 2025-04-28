/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:36:28 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/14 16:52:38 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_value_env(char *key, t_env *env)
{
	if (!key)
		return (0);
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

void	get_env_value(char *str, char *expanded, int *i, t_mini *shell)
{
	char	c;
	char	*value;
	int		start;

	if (str[*i + 1] == '?')
	{
		if_expand(shell, expanded, i);
		return ;
	}
	if (!is_env_valid(str[*i + 1], 1))
	{
		ft_strncat(expanded, str + (*i)++, 1);
		return ;
	}
	start = ++(*i);
	while (is_env_valid(str[*i], 0))
		(*i)++;
	c = str[*i];
	str[*i] = 0;
	value = get_value_env(str + start, shell->env_list);
	if (!value)
		return ;
	ft_strncat(expanded, value, ft_strlen(value));
	str[*i] = c;
	return ;
}

int	get_value_len(char *key, t_env *env)
{
	if (!key)
		return (0);
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (ft_strlen(env->content));
		env = env->next;
	}
	return (0);
}

bool	is_env_valid(char c, bool start)
{
	if (start)
		return (ft_isalpha(c) || c == '_');
	else
		return (ft_isalnum(c) || c == '_');
}

int	get_env_size(char *str, int *i, t_mini *shell)
{
	char	c;
	int		start;
	int		len;
	char	*ibaby;

	if (str[*i + 1] == '?')
	{
		ibaby = ft_itoa(shell->state);
		len = ft_strlen(ibaby);
		(*i) += 2;
		return (free(ibaby), len);
	}
	if (!is_env_valid(str[(*i) + 1], 1))
		return ((*i)++, 1);
	start = ++(*i);
	while (is_env_valid(str[*i], 0))
	{
		(*i)++;
	}
	c = str[*i];
	str[*i] = 0;
	len = get_value_len(str + start, shell->env_list);
	str[*i] = c;
	return (len);
}
