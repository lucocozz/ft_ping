/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_datagram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:42:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/06 01:11:39 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_recv_data	ping_datagram(int socket, t_icmp_datagram datagram, struct addrinfo *address)
{
	t_recv_data		data;
	struct timeval	start, end;

	if (gettimeofday(&start, NULL) < 0)
		return ((t_recv_data){.error = ERR_UNDEFINED});
	send_datagram(socket, datagram, address);
	data = recv_datagram(socket, address->ai_family);
	if (gettimeofday(&end, NULL) < 0)
		return ((t_recv_data){.error = ERR_UNDEFINED});
	data.time = get_elapsed_time(start, end);
	return (data);
}
