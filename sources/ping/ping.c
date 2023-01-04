/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:39:15 by lucocozz          #+#    #+#             */
/*   Updated: 2022/12/30 12:40:17 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int ping(t_options options, struct addrinfo *address, int socket)
{
	char			*ip;
	int				result;
	t_icmp_datagram	datagram;

	ip = get_ip_address(address);
	if (ip == NULL)
		return (-1);
	datagram = create_icmp_datagram(options.size, ICMP_ECHO, 0);
	if (datagram.raw == NULL) {
		free(ip);
		return (-1);
	}
	datagram.header->checksum = checksum(datagram.raw, datagram.total);
	print_ping_header(options, ip, datagram);
	for (uint i = 0; g_running == true && i != options.count; ++i) {
		result = send_and_recv_datagram(options, socket, datagram, address, ip, i + 1);
		if (result == -1)
			break ;
		if (i != options.count - 1)
			usleep(options.interval);
	}
	free(ip);
	delete_icmp_datagram(&datagram);
	return (result);
}
