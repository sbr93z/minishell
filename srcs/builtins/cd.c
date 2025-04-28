/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:16:01 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/19 03:56:22 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_getenv(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

static int	ft_update_env(t_env **env, char *key, char *new_value,
		t_gc_list *gc)
{
	t_env	*tmp;

	(void)gc;
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(new_value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

static char	*ft_cd_moins(t_env **env, char *new_path, t_mini *shell)
{
	new_path = ft_getenv(*env, "OLDPWD");
	if (!new_path)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		shell->state = 1;
		return (NULL);
	}
	printf("%s\n", new_path);
	return (new_path);
}

int	ft_cd(t_env **env, char *path, t_gc_list *gc, t_mini *shell)
{
	char	*oldpwd;
	char	*new_path;

	new_path = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!path)
		new_path = ft_getenv(*env, "HOME");
	else if (ft_strcmp(path, "-") == 0)
		new_path = ft_cd_moins(env, new_path, shell);
	else
		new_path = path;
	if (!new_path || chdir(new_path) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (0);
	}
	ft_update_env(env, "OLDPWD", oldpwd, gc);
	free(oldpwd);
	oldpwd = getcwd(NULL, 0);
	ft_update_env(env, "PWD", oldpwd, gc);
	shell->state = 0;
	return (free(oldpwd), 1);
}
