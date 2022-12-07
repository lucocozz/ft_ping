/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:58:25 by user42            #+#    #+#             */
/*   Updated: 2022/12/07 18:00:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	uint i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((u_char)s1[i] - (u_char)s2[i]);
		i++;
	}
	return (0);
}

uint	ft_strlen(const char *str)
{
	uint	i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}