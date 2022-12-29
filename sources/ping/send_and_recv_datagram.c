/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_and_recv_datagram.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:42:34 by lucocozz          #+#    #+#             */
/*   Updated: 2022/12/29 16:43:20 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	send_and_recv_datagram(int socket, t_icmp_datagram datagram,
		struct addrinfo *address, char *ip, int seq)
{
	int				bytes;
	struct timeval	start, end;

	if (gettimeofday(&start, NULL) < 0)
		return (-1);
	send_datagram(socket, datagram, address);
	bytes = recv_datagram(socket, address);
	if (gettimeofday(&end, NULL) < 0)
		return (-1);
	print_ping_result(bytes, ip, seq, get_elapsed_time(start, end));
	return (bytes);
}
