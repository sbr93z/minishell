/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:16:16 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/25 16:25:13 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	extract_key_and_validate(char *arg, char **key, t_mini *shell)
{
	if (ft_strchr(arg, '='))
		*key = gc_substr(arg, 0, ft_strchr(arg, '=') - arg, shell->gc);
	else
		*key = gc_strdup(arg, shell->gc);
	if (!is_valid_identifier(*key))
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		if (!ft_strchr(arg, '='))
			free(*key);
		shell->state = 1;
		return (0);
	}
	return (1);
}

int	process_valid_key(char *arg, char *key, t_env **env_list, t_gc_list *gc)
{
	char	*content;

	if (ft_strchr(arg, '='))
	{
		content = strdup(ft_strchr(arg, '=') + 1);
		if (!key || !content)
		{
			free(key);
			free(content);
			return (0);
		}
		var_update(env_list, key, content);
	}
	else
	{
		if (handle_variable_lookup(arg, env_list))
			return (1);
		content = gc_strdup("", gc);
		if (!key || !content)
			return (free(content), free(key), 0);
		env_add_back(env_list, env_new_node(key, content));
	}
	return (1);
}

static int	process_arg(char *arg, t_env **env_list, t_mini *shell)
{
	char	*key;
	char	*content;

	if (!extract_key_and_validate(arg, &key, shell))
		return (0);
	if (ft_strchr(arg, '='))
		return (handle_assignment(arg, env_list, shell->gc));
	if (handle_variable_lookup(arg, env_list))
		return (1);
	key = ft_strdup(arg);
	content = ft_strdup("");
	if (!key || !content)
	{
		free(key);
		free(content);
		return (0);
	}
	env_add_back(env_list, env_new_node(key, content));
	shell->state = 0;
	return (1);
}

int	cmd_export(char **args, t_env **env_list, t_mini *shell)
{
	int	i;

	if (!args[1])
	{
		display_env(*env_list, shell->gc);
		return (1);
	}
	i = 1;
	while (args[i])
	{
		if (!process_arg(args[i], env_list, shell))
			return (0);
		i++;
	}
	return (1);
}

int	handle_assignment(char *arg, t_env **env_list, t_gc_list *gc)
{
	char	*key;
	char	*content;
	char	*raw_content;

	key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(key);
		return (0);
	}
	raw_content = ft_strchr(arg, '=') + 1;
	content = strip_quotes(raw_content, gc);
	if (!key || !content)
	{
		free(key);
		free(content);
		return (0);
	}
	var_update(env_list, key, content);
	return (1);
}
