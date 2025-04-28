/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:49:22 by sferrad           #+#    #+#             */
/*   Updated: 2025/03/19 13:49:23 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac == 1)
	{
		ft_prompt(env);
	}
	else
		printf("Invalid Format : ./minishell\n");
	return (0);
}
