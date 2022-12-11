/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:59:06 by user42            #+#    #+#             */
/*   Updated: 2022/12/11 19:09:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <sys/types.h>
# include <stdint.h>
# include <stdbool.h>

typedef unsigned char	u_char;
typedef unsigned int	uint;

int		ft_strcmp(const char *s1, const char *s2);
uint	ft_strlen(const char *str);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
float	ft_atof(const char *str);
bool	ft_is_integer(const char *str);
bool	ft_is_float(const char *str);

#endif
