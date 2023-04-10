/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_datagram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:07:12 by lucocozz          #+#    #+#             */
/*   Updated: 2023/04/10 11:13:20 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

struct msghdr	__init_msg(struct sockaddr_in *src_addr, struct iovec *iov)
{
	struct msghdr	msg = {0};
	
	msg.msg_name = src_addr;
	msg.msg_namelen = sizeof(*src_addr);
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	return (msg);
}

static int	__get_ttl(struct msghdr header, int level)
{
	int					ttl = -1;
	struct cmsghdr		*ctrl_msg = NULL;

	ctrl_msg = CMSG_FIRSTHDR(&header);
	while (ctrl_msg != NULL)
	{
		if (ctrl_msg->cmsg_level == level && ctrl_msg->cmsg_type == IP_TTL)
		{
			ttl = *((int *)CMSG_DATA(ctrl_msg));
			break ;
		}
		CMSG_NXTHDR(&header, ctrl_msg);
	}
	return (ttl);
}

static int	__get_error_type(void **buffer)
{
	struct icmphdr *icmp_header = (struct icmphdr *)(*buffer + sizeof(struct iphdr));

	if (icmp_header->type == ICMP_ECHOREPLY && icmp_header->un.echo.id != getpid())
		return (ERR_WRONG_ID);
	if (icmp_header->type == ICMP_TIME_EXCEEDED && icmp_header->code == 0)
		return (ERR_TTL_EXCEEPTED);
	if (icmp_header->type == ICMP_DEST_UNREACH && icmp_header->code == 0)
		return (ERR_NET_UNREACHABLE);
	return (NOERROR);
}

static short	__get_error(int bytes, void **buffer)
{
	if (bytes == -1)
	{
		if (errno == EINTR)
			return (INTERRUPTED);
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return (ERR_TIMEOUT);
		return (ERR_UNDEFINED);
	}
	return (__get_error_type(buffer));
}

t_querie	recv_datagram(t_cli cli, int socket, int family)
{
	struct iovec		iov;
	struct msghdr		msg;
	struct sockaddr_in	from_addr = {0};
	char				buffer[MSG_BUFFER_SIZE] = {0};
	int					ctrl_buffer[CMSG_SPACE(sizeof(int))] = {0};
	t_querie			querie = {0};

	iov.iov_base = buffer;
	iov.iov_len = MSG_BUFFER_SIZE;
	msg = __init_msg(&from_addr, &iov);
	msg.msg_control = ctrl_buffer;
	msg.msg_controllen = CMSG_SPACE(sizeof(ctrl_buffer));
	querie.bytes = recvmsg(socket, &msg, 0);
	querie.error = __get_error(querie.bytes, &msg.msg_iov->iov_base);
	if (querie.error == NOERROR) {
		querie.ttl = __get_ttl(msg, GET_LEVEL(family));
	}
	inet_ntop(family, &from_addr.sin_addr, querie.from_addr, GET_ADDRLEN(family));
	if (cli.no_dns == false)
		getnameinfo((struct sockaddr*)&from_addr, sizeof(from_addr), querie.ptr_record, PTR_RECORD_SIZE, NULL, 0, 0);
	else
		ft_strcpy(querie.ptr_record, querie.from_addr);
	return (querie);
}
