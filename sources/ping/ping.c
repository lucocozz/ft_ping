/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:39:15 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/05 16:52:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int ping(t_options options, struct addrinfo *address, int socket)
{
	char			*ip;
	t_recv_data		result;
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
		result = ping_datagram(socket, datagram, address);
		print_ping_result(options, result, ip, i + 1);
		if (result.error == ERR_UNDEFINED)
			break ;
		if (i != options.count - 1)
			usleep(options.interval);
	}
	free(ip);
	delete_icmp_datagram(&datagram);
	return (result.error);
}
