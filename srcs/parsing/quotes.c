/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:06:45 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/07 15:07:06 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	is_only_empty_quotes(char *buffer)
{
	int	i;
	int	found_content;

	i = 0;
	found_content = 0;
	while (buffer[i])
	{
		if (buffer[i] != '"' && buffer[i] != '\'' && !ft_isspace(buffer[i]))
			found_content = 1;
		i++;
	}
	return (!found_content);
}
