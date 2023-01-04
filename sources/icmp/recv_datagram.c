/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_datagram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:07:12 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/04 17:17:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

struct msghdr	__init_msg(struct sockaddr address)
{
	struct iovec	iov;
	struct msghdr	msg;
	char			buffer[2048];
	int				ctrl_buffer[CMSG_SPACE(sizeof(int))];
	
	iov.iov_base = buffer;
	iov.iov_len = sizeof(buffer);
	msg.msg_name = &address;
	msg.msg_namelen = sizeof(address);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = ctrl_buffer;
	msg.msg_controllen = CMSG_SPACE(sizeof(ctrl_buffer));
	return (msg);
}

static int	__get_ttl(struct msghdr header, int level)
{
	int					ttl = -1;
	struct cmsghdr		*ctrl_msg;

	ctrl_msg = CMSG_FIRSTHDR(&header);
	while (ctrl_msg != NULL) {
		if (ctrl_msg->cmsg_level == level && ctrl_msg->cmsg_type == IP_TTL) {
			ttl = *((int *)CMSG_DATA(ctrl_msg));
			break ;
		}
		CMSG_NXTHDR(&header, ctrl_msg);
	}
	return (ttl);
}

static bool	__ttl_exceeded(struct msghdr *msg)
{
	struct icmphdr *icmp_header = (struct icmphdr *)msg->msg_iov[0].iov_base;

	printf("type: %d\ncode: %d\n", icmp_header->type, icmp_header->code);
	if (icmp_header->type == ICMP_TIME_EXCEEDED && icmp_header->code == 0)
		return (true);
	return (false);
}

t_recv_data	recv_datagram(int socket, struct addrinfo *address)
{
	struct msghdr		msg;
	t_recv_data			data = {.timeout = false, .ttl_exceeced = false};

	msg = __init_msg(*address->ai_addr);
	data.bytes = recvmsg(socket, &msg, MSG_ERRQUEUE | MSG_DONTWAIT);
	if (data.bytes == -1) {
		printf("bytes = %d\n", data.bytes);
		if (errno == EAGAIN || errno == EWOULDBLOCK) {
			data.timeout = true;
			return (data);
		}
		printf("error: %s\n", strerror(errno));
		return (data);
	}
	else if (msg.msg_flags & MSG_ERRQUEUE)
	{
		data.ttl_exceeced = __ttl_exceeded(&msg);
		return (data);
	}
	data.ttl = __get_ttl(msg, GET_LEVEL(address->ai_family));
	return (data);
}
