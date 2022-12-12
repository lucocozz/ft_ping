/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:58:25 by user42            #+#    #+#             */
/*   Updated: 2022/12/12 18:38:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	for (uint i = 0; (s1[i] != '\0' || s2[i] != '\0'); ++i)
		if (s1[i] != s2[i])
			return ((u_char)s1[i] - (u_char)s2[i]);
	return (0);
}

uint	ft_strlen(const char *str)
{
	uint	i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}

static bool	ft_isspace(int c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (true);
	return (false);
}

int	ft_atoi(const char *str)
{
	int		i = 0;
	int		value = 0;
	short	sign = 1;

	while (ft_isspace(str[i]) == true)
		i++;
	if (str[i] == '-' || str[i] == '+') {
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	for (; str[i] >= '0' && str[i] <= '9'; ++i)
		value = value * 10 + (str[i] - '0');
	return (sign * value);
}

long	ft_atol(const char *str)
{
	int		i = 0;
	int		value = 0;
	short	sign = 1;

	while (ft_isspace(str[i]) == true)
		i++;
	if (str[i] == '-' || str[i] == '+') {
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	for (; str[i] >= '0' && str[i] <= '9'; ++i)
		value = value * 10 + (str[i] - '0');
	return (sign * value);
}

float	ft_atof(const char *str)
{
	int		i = 0;
	short	sign = 1;
	int		divisor = 1;
	double	integer = 0;
	double	fraction = 0;
	bool	in_fraction = false;

	while (ft_isspace(str[i]) == true)
		i++;
	if (str[i] == '-' || str[i] == '+') {
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	for (; str[i] != '\0'; ++i)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (in_fraction == true) {
				fraction = fraction * 10 + (str[i] - '0');
				divisor *= 10;
			}
			else
				integer = integer * 10 + (str[i] - '0');
		}
		else if (str[i] == '.')
		{
			if (in_fraction == true)
				return (sign * (integer + fraction / divisor));
			else
				in_fraction = true;
		}
		else
			return (sign * (integer + fraction / divisor));
	}
	return (sign * (integer + fraction / divisor));
}

bool	ft_is_integer(const char *str)
{
	for (uint i = 0; str[i] != '\0'; ++i)
		if (str[i] != '-' && !(str[i] >= '0' && str[i] <= '9'))
			return (false);
	return (true);
}

bool	ft_is_float(const char *str)
{
	for (uint i = 0; str[i] != '\0'; ++i)
		if (str[i] != '-' && !(str[i] >= '0' && str[i] <= '9') && str[i] != '.')
			return (false);
	return (true);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr = s;

	for (uint i = 0; i < n; ++i)
		ptr[i] = 0;
}
