/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_datagram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:07:12 by lucocozz          #+#    #+#             */
/*   Updated: 2022/12/29 16:16:20 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	recv_datagram(int socket, struct addrinfo *address)
{
	struct iovec		iov;
	struct msghdr		msg;
	int					bytes;
	char				buffer[1024];
	struct sockaddr_in	name = *(struct sockaddr_in *)address->ai_addr;
	socklen_t			name_len = sizeof(name);

	iov.iov_base = buffer;
	iov.iov_len = sizeof(buffer);
	msg.msg_name = &name;
	msg.msg_namelen = name_len;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	bytes = recvmsg(socket, &msg, 0);
	return (bytes);
}
