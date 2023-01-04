/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_and_recv_datagram.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:42:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/03 16:07:03 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	send_and_recv_datagram(t_options options, int socket, t_icmp_datagram datagram,
		struct addrinfo *address, char *ip, int seq)
{
	t_recv_data		data;
	struct timeval	start, end;

	if (gettimeofday(&start, NULL) < 0)
		return (-1);
	send_datagram(socket, datagram, address);
	data = recv_datagram(socket, address);
	if (data.bytes == -1 || data.ttl == -1)
		return (-1);
	if (gettimeofday(&end, NULL) < 0)
		return (-1);
	data.time = get_elapsed_time(start, end);
	print_ping_result(options, data, ip, seq);
	return (0);
}
