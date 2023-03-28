/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_datagram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 00:09:19 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/28 19:13:16 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	send_datagram(int socket, t_icmp_datagram datagram, struct addrinfo *address)
{
	struct sockaddr_in	dest = {0};
	struct sockaddr_in	*sockaddr = (struct sockaddr_in *)address->ai_addr;
	int					bytes_sent;

	dest.sin_family = address->ai_family;
	dest.sin_addr = sockaddr->sin_addr;
	bytes_sent = sendto(socket, datagram.raw, datagram.total, 0, (struct sockaddr *)&dest, sizeof(dest));
	return (bytes_sent);
}
