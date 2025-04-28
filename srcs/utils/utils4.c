/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:56:07 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/25 17:09:02 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	help_display_env(t_env *env, t_display_env *vars, t_gc_list *gc)
{
	vars->current = env;
	while (vars->current)
	{
		condition_help_display(vars, gc);
		vars->current = vars->current->next;
	}
}

void	display_env(t_env *env, t_gc_list *gc)
{
	t_display_env	vars;
	t_env			*temp;

	if (!env)
		return ;
	vars.sorted = NULL;
	help_display_env(env, &vars, gc);
	vars.current = vars.sorted;
	while (vars.current)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(vars.current->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(vars.current->content, 1);
		ft_putstr_fd("\"\n", 1);
		vars.current = vars.current->next;
	}
	while (vars.sorted)
	{
		temp = vars.sorted->next;
		free(vars.sorted->key);
		free(vars.sorted->content);
		free(vars.sorted);
		vars.sorted = temp;
	}
}

char	**extract_args_from_token(t_token *token, int *arg_count, t_gc_list *gc)
{
	char	**args;
	t_token	*current;
	int		i;

	*arg_count = 0;
	current = token;
	while (current && (current == token || current->type == STRING))
	{
		(*arg_count)++;
		current = current->next;
	}
	args = gc_malloc((*arg_count + 1) * sizeof(char *), gc);
	if (!args)
		return (NULL);
	current = token;
	i = 0;
	while (i < *arg_count && current && (current == token
			|| current->type == STRING))
	{
		args[i] = current->arg;
		current = current->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	handle_absolute_path(char *cmd, t_mini *shell)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == -1)
	{
		if (!shell->is_arg)
		{
			shell->state = 127;
			return (print_error(cmd, ": No such file or directory\n", 0));
		}
		return (0);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		if (!shell->is_arg)
		{
			shell->state = 126;
			return (print_error(cmd, ": Is a directory\n", 0));
		}
		return (0);
	}
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0)
		return (print_error(cmd, ": Permission denied\n", 0));
	return (1);
}

char	*get_env_path(t_mini *shell, t_gc_list *gc)
{
	int		i;
	char	**paths;

	i = 0;
	while (shell->envp[i] && ft_strnstr(shell->envp[i], "PATH=", 5) == 0)
		i++;
	if (!shell->envp[i])
		return (NULL);
	paths = gc_split(shell->envp[i] + 5, ':', gc);
	return ((char *)paths);
}
