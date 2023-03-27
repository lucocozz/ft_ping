/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_queries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:42:34 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/27 19:01:29 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_querie	ping_queries(t_cli cli, int socket, t_icmp_datagram datagram,
	struct addrinfo *address)
{
	t_querie		querie;
	struct timeval	start, end;

	if (gettimeofday(&start, NULL) < 0)
		return ((t_querie){.error = ERR_UNDEFINED});
	if (send_datagram(socket, datagram, address) == -1)
		verbose(STDERR_FILENO, cli.verbose, "send error\n");
	querie = recv_datagram(cli, socket, address->ai_family);
	if (gettimeofday(&end, NULL) < 0)
		return ((t_querie){.error = ERR_UNDEFINED});
	querie.time = get_elapsed_time(start, end);
	return (querie);
}
