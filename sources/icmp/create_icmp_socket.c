/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_icmp_socket.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:33:49 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/03 16:50:03 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	__set_options(t_options options, int raw_socket, int level)
{
	int enable = 1;
	
	setsockopt(raw_socket, level, IP_RECVERR, &enable, sizeof(enable));
	setsockopt(raw_socket, level, IP_TTL, &options.ttl, sizeof(options.ttl));
	setsockopt(raw_socket, level, IP_RECVTTL, &enable, sizeof(enable));
	setsockopt(raw_socket, level, SO_RCVTIMEO, &options.timeout, sizeof(options.timeout));
	if (options.timestamps == true)
		setsockopt(raw_socket, level, IPOPT_TIMESTAMP, &options.timestamps, sizeof(options.timestamps));
}

int	create_icmp_socket(t_options options, struct addrinfo *address)
{
	int		raw_socket;
	int		level = GET_LEVEL(address->ai_family);

	raw_socket = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
	if (raw_socket == -1)
		return (-1);
	__set_options(options, raw_socket, level);
	return (raw_socket);
}
