/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:59:06 by user42            #+#    #+#             */
/*   Updated: 2022/12/07 18:30:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <sys/types.h>
# include <stdint.h>

typedef unsigned char	u_char;
typedef unsigned int	uint;

int		ft_strcmp(const char *s1, const char *s2);
uint	ft_strlen(const char *str);

#endif
