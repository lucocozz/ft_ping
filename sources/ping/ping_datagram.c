/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_datagram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:42:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/26 14:37:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_recv_data	ping_datagram(t_options options, int socket, t_icmp_datagram datagram,
	struct addrinfo *address)
{
	t_recv_data		data;
	struct timeval	start, end;

	if (gettimeofday(&start, NULL) < 0)
		return ((t_recv_data){.error = ERR_UNDEFINED});
	if (send_datagram(socket, datagram, address) == -1)
		verbose(STDERR_FILENO, options.verbose, "send error\n");
	data = recv_datagram(options, socket, address->ai_family);
	if (gettimeofday(&end, NULL) < 0)
		return ((t_recv_data){.error = ERR_UNDEFINED});
	data.time = get_elapsed_time(start, end);
	return (data);
}
