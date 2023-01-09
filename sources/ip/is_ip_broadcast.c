/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ip_broadcast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:15:04 by user42            #+#    #+#             */
/*   Updated: 2023/01/09 15:38:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	is_ip_broadcast(int family, char *ip)
{
	struct in_addr	addr;

	if (inet_pton(family, ip, &addr) != 1)
		return (-1);
	if (addr.s_addr == INADDR_BROADCAST)
		return (1);
	return (0);
}
