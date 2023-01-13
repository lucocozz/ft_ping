/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ip_netmask.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:23:06 by user42            #+#    #+#             */
/*   Updated: 2023/01/13 20:37:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

char	*get_ip_netmask(char *ip_address)
{
	struct in_addr	address;
	unsigned char	first_octet;

	inet_aton(ip_address, &address);
	first_octet = (address.s_addr >> 24) & 0xff;
	printf("first octet: %d\n", first_octet);
	if (first_octet >= 1 && first_octet <= 126)
		return (NETMASK_A);
	else if (first_octet >= 128 && first_octet <= 191)
		return (NETMASK_B);
	else if (first_octet >= 224 && first_octet <= 239)
		return (NETMASK_C);
	else if (first_octet >= 240 && first_octet <= 255)
		return (NETMASK_D);
	else
		return (NULL);
}
