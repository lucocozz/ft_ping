/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_icmp_socket.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:33:49 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/05 00:57:17 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int	__set_options(t_options options, int raw_socket, int level)
{
	int enable = 1;
	
	// if (setsockopt(raw_socket, level, IP_RECVERR, &enable, sizeof(enable)) < 0)
		// return (-1);
	if (setsockopt(raw_socket, level, IP_TTL, &options.ttl, sizeof(options.ttl)) < 0)
		return (-1);
	if (setsockopt(raw_socket, level, IP_RECVTTL, &enable, sizeof(enable)) < 0)
		return (-1);
	if (setsockopt(raw_socket, SOL_SOCKET, SO_RCVTIMEO, &options.timeout, sizeof(options.timeout)) < 0)
		return (-1);
	// if (setsockopt(raw_socket, level, IPOPT_TIMESTAMP, &options.timestamps, sizeof(options.timestamps)) < 0)
		// return (-1);
	return (0);
}

int	create_icmp_socket(t_options options, struct addrinfo *address)
{
	int		raw_socket;

	raw_socket = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
	if (raw_socket == -1)
		return (-1);
	if (__set_options(options, raw_socket, GET_LEVEL(address->ai_family)) == -1)
		printf("set_options error: %s\n", strerror(errno));
	return (raw_socket);
}
