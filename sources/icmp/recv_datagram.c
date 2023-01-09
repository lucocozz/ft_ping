/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_datagram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:07:12 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/09 18:35:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

struct msghdr	__init_msg(struct sockaddr_in *src_addr, struct iovec *iov)
{
	struct msghdr	msg = {0};
	int				ctrl_buffer[CMSG_SPACE(sizeof(int))];
	
	msg.msg_name = src_addr;
	msg.msg_namelen = sizeof(*src_addr);
	msg.msg_iov = iov;
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

static bool	__ttl_exceeded(void **buffer)
{
	struct icmphdr *icmp_header = (struct icmphdr *)(*buffer + sizeof(struct iphdr));

	if (icmp_header->type == ICMP_TIME_EXCEEDED && icmp_header->code == 0)
		return (ERR_TTL_EXCEEPTED);
	return (NOERROR);
}

static short	__get_error(int bytes, void **buffer)
{
	if (bytes == -1) {
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return (ERR_TIMEOUT);
		else if (errno == ENETUNREACH)
			return (ERR_NET_UNREACHABLE);
		return (ERR_UNDEFINED);
	}
	return (__ttl_exceeded(buffer));
}

t_recv_data	recv_datagram(t_options options, int socket, int family)
{
	struct iovec		iov;
	struct msghdr		msg;
	struct sockaddr_in	from_addr;
	char				buffer[MSG_BUFFER_SIZE];
	t_recv_data			data = {.error = NOERROR};

	iov.iov_base = buffer;
	iov.iov_len = MSG_BUFFER_SIZE;
	msg = __init_msg(&from_addr, &iov);
	data.bytes = recvmsg(socket, &msg, 0);
	data.error = __get_error(data.bytes, &msg.msg_iov->iov_base);
	if (data.error == NOERROR) {
		data.ttl = __get_ttl(msg, GET_LEVEL(family));
	}
	inet_ntop(family, &from_addr.sin_addr, data.from_addr, GET_ADDRLEN(family));
	if (options.no_dns == false)
		getnameinfo((struct sockaddr*)&from_addr, sizeof(from_addr), data.ptr_record, PTR_RECORD_SIZE, NULL, 0, 0);
	else
		ft_strcpy(data.ptr_record, data.from_addr);
	return (data);
}
