/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:36:11 by sferrad           #+#    #+#             */
/*   Updated: 2024/11/17 19:18:13 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_sep(char c, const char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		debut;
	int		fin;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && is_sep(s1[i], set) == 1)
		i++;
	debut = i;
	fin = ft_strlen(s1);
	while (fin > 0 && is_sep(s1[fin - 1], set))
		fin--;
	if (debut >= fin)
		return (ft_strdup(""));
	str = malloc((fin - debut + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (debut < fin)
		str[i++] = s1[debut++];
	str[i] = '\0';
	return (str);
}
