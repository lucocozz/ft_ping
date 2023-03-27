/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:39:15 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/27 19:13:03 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int ping(t_cli cli, struct addrinfo *address, int socket)
{
	char			*ip;
	t_querie		querie;
	t_icmp_datagram	datagram;

	datagram = create_icmp_datagram(cli.size, ICMP_ECHO, 0);
	if (datagram.raw == NULL)
		return (-1);
	datagram.header->checksum = checksum(datagram.raw, datagram.total);
	ip = get_ip_address(address);
	if (ip == NULL)
		return (-1);
	print_ping_header(cli, ip, datagram);
	free(ip);
	for (uint i = 0; g_ping.running == true && i != cli.count; ++i)
	{
		querie = ping_queries(cli, socket, datagram, address);
		if (querie.error == ERR_WRONG_ID)
			continue;
		print_ping_result(cli, querie, i + 1);
		set_ping_stats(querie);
		if (querie.error == ERR_UNDEFINED)
			break ;
		if (i != cli.count - 1 && querie.error != INTERRUPTED)
			usleep(cli.interval);
	}
	print_ping_stats(cli);
	delete_icmp_datagram(&datagram);
	return (querie.error);
}
