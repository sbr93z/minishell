/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:56:12 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/25 01:51:31 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*generate_token(char *arg, t_mini *shell, t_gc_list *gc)
{
	t_token	*new_token;

	if (is_redirect(arg))
	{
		new_token = ft_lstnew_mini(arg, REDIRECT, gc);
	}
	else if (!ft_strcmp(arg, "|"))
	{
		shell->in_command = 0;
		new_token = ft_lstnew_mini(arg, PIPE, gc);
	}
	else if (!shell->in_command)
	{
		new_token = create_token_by_type(arg, shell, gc);
		shell->in_command = 1;
	}
	else
		new_token = ft_lstnew_mini(arg, STRING, gc);
	return (new_token);
}

t_token	*tokenize(char **args, t_mini *shell, t_gc_list *gc)
{
	t_token	*token_list;
	t_token	*new_token;
	int		i;
	int		first_is_redirect;

	i = 0;
	token_list = NULL;
	first_is_redirect = 0;
	if (args[0] && is_redirect(args[0]))
		first_is_redirect = 1;
	shell->in_command = 0;
	while (args[i])
	{
		if (i == 0 && first_is_redirect)
			new_token = ft_lstnew_mini(args[i], REDIRECT, gc);
		else
			new_token = generate_token(args[i], shell, gc);
		if (!ft_tokenadd_back(&token_list, new_token))
			return (gc_free_all(gc), NULL);
		i++;
	}
	return (token_list);
}

void	print_token_type(int type)
{
	if (type == BUILTIN)
		printf("BUILTIN\n");
	else if (type == CMD)
		printf("CMD\n");
	else if (type == REDIRECT)
		printf("REDIRECT\n");
	else if (type == PIPE)
		printf("PIPE\n");
	else
		printf("STRING\n");
}

bool	is_builtin(char **arg)
{
	if (arg == NULL || arg[0] == NULL)
		return (0);
	if (ft_strcmp("cd", arg[0]) == 0)
		return (1);
	if (ft_strcmp("echo", arg[0]) == 0)
		return (1);
	if (ft_strcmp("env", arg[0]) == 0)
		return (1);
	if (ft_strcmp("exit", arg[0]) == 0)
		return (1);
	if (ft_strcmp("export", arg[0]) == 0)
		return (1);
	if (ft_strcmp("pwd", arg[0]) == 0)
		return (1);
	if (ft_strcmp("unset", arg[0]) == 0)
		return (1);
	return (0);
}

int	is_redirect(char *str)
{
	if (!str)
		return (0);
	if (!strcmp(str, "<") || !strcmp(str, ">") || !strcmp(str, "<<")
		|| !strcmp(str, ">>"))
		return (1);
	return (0);
}
