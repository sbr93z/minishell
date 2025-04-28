/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:56:00 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/25 00:51:09 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	while (s[i] != '\0')
	{
		i2 = 0;
		while (reject[i2] != '\0')
		{
			if (s[i] == reject[i2])
				return (i);
			i2++;
		}
		i++;
	}
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	**extract_args(t_token *token, int *arg_count, t_gc_list *gc)
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

int	handle_builtin(t_token *token, t_mini *shell, t_gc_list *gc)
{
	char	**args;
	int		ret;
	int		arg_count;

	args = extract_args(token, &arg_count, gc);
	if (!args)
		return (0);
	ret = 1;
	if (ft_strcmp(args[0], "env") == 0)
		printf_env(shell->env_list, shell);
	else if (ft_strcmp(args[0], "export") == 0)
		ret = cmd_export(args, &(shell->env_list), shell);
	else
		ret = 0;
	return (ret);
}

int	handle_empty_input(t_mini *shell)
{
	if (ft_strlen(shell->buffer) == 0)
		return (1);
	return (0);
}

void	condition_help_display(t_display_env *vars, t_gc_list *gc)
{
	(void)gc;
	vars->copy = malloc(sizeof(t_env));
	if (!vars->copy)
		return ;
	vars->copy->key = ft_strdup(vars->current->key);
	vars->copy->content = ft_strdup(vars->current->content);
	vars->copy->next = NULL;
	if (!vars->sorted || ft_strcmp(vars->copy->key, vars->sorted->key) < 0)
	{
		vars->copy->next = vars->sorted;
		vars->sorted = vars->copy;
	}
	else
	{
		vars->temp = vars->sorted;
		vars->prev = NULL;
		while (vars->temp && ft_strcmp(vars->copy->key, vars->temp->key) > 0)
		{
			vars->prev = vars->temp;
			vars->temp = vars->temp->next;
		}
		vars->copy->next = vars->temp;
		if (vars->prev)
			vars->prev->next = vars->copy;
	}
}
