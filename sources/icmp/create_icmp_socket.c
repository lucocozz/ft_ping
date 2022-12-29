/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_icmp_socket.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:33:49 by lucocozz          #+#    #+#             */
/*   Updated: 2022/12/29 15:35:15 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	create_icmp_socket(t_options options, struct addrinfo *address)
{
	int		raw_socket;
	int		level = (address->ai_family == PF_INET ? IPPROTO_IP : IPPROTO_IPV6);

	raw_socket = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
	if (raw_socket == -1)
		return (-1);
	setsockopt(raw_socket, level, IP_TTL, &options.ttl, sizeof(options.ttl));
	if (options.timestamps == true)
		setsockopt(raw_socket, level, IPOPT_TIMESTAMP, &options.timestamps, sizeof(options.timestamps));
	return (raw_socket);
}
