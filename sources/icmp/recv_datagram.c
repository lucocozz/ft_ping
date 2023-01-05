/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_datagram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:07:12 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/05 02:04:31 by lucocozz         ###   ########.fr       */
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

static bool	__ttl_exceeded(struct msghdr msg)
{
	struct icmphdr *icmp_header = (struct icmphdr *)(msg.msg_iov->iov_base + sizeof(struct iphdr));

	if (icmp_header->type == ICMP_TIME_EXCEEDED && icmp_header->code == 0)
		return (ERR_TTL_EXCEEPTED);
	return (NOERROR);
}

//TODO: comprendre pourquoi ttl exceeced fail quand est appeler dans une sous fonction

static short	__get_error(int bytes, struct msghdr msg)
{
	// (void)msg;
	if (bytes == -1) {
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return (ERR_TIMEOUT);
		return (ERR_UNDEFINED);
	}
	// return (NOERROR);
	return (__ttl_exceeded(msg));
}

t_recv_data	recv_datagram(int socket, struct addrinfo *address)
{
	struct msghdr		msg;
	t_recv_data			data = {.error = NOERROR};

	msg = __init_msg(*address->ai_addr);
	data.bytes = recvmsg(socket, &msg, 0);
	data.error = __get_error(data.bytes, msg);
	// data.error = __ttl_exceeded(msg);
	data.ttl = __get_ttl(msg, GET_LEVEL(address->ai_family));
	return (data);
}
