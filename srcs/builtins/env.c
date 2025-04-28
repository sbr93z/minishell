/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:16:06 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/19 03:30:48 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*env_new_node(char *key, char *content)
{
	t_env	*node;

	node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->content = content;
	node->next = NULL;
	return (node);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (!*env)
	{
		*env = new;
		return ;
	}
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_env	*init_env(char **envp, t_gc_list *gc)
{
	t_env_init	vars;

	(void)gc;
	vars.env = NULL;
	vars.i = 0;
	while (envp[vars.i])
	{
		vars.equal = ft_strchr(envp[vars.i], '=');
		if (!vars.equal)
		{
			vars.i++;
			continue ;
		}
		vars.key = ft_substr(envp[vars.i], 0, vars.equal - envp[vars.i]);
		vars.content = ft_strdup(vars.equal + 1);
		vars.new = env_new_node(vars.key, vars.content);
		if (!vars.new)
			return (NULL);
		env_add_back(&vars.env, vars.new);
		vars.i++;
	}
	return (vars.env);
}

int	printf_env(t_env *env, t_mini *shell)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->content);
		env = env->next;
	}
	shell->state = 0;
	return (0);
}
