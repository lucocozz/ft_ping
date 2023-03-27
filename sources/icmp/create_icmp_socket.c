/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_icmp_socket.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:33:49 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/27 18:58:34 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void __set_filter(int raw_socket)
{
	static int once;
	static struct sock_filter insns[] = {
		BPF_STMT(BPF_LDX | BPF_B   | BPF_MSH, 0),	/* Skip IP header due BSD, see ping6. */
		BPF_STMT(BPF_LD  | BPF_H   | BPF_IND, 4),	/* Load icmp echo ident */
		BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0xAAAA, 0, 1), /* Ours? */
		BPF_STMT(BPF_RET | BPF_K, ~0U),			/* Yes, it passes. */
		BPF_STMT(BPF_LD  | BPF_B   | BPF_IND, 0),	/* Load icmp type */
		BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, ICMP_ECHOREPLY, 1, 0), /* Echo? */
		BPF_STMT(BPF_RET | BPF_K, 0xFFFFFFF),		/* No. It passes. */
		BPF_STMT(BPF_RET | BPF_K, 0)			/* Echo with wrong ident. Reject. */
	};
	static struct sock_fprog filter = {
		.len = sizeof(insns) / sizeof(insns[0]),
		.filter = insns
	};
	if (once)
		return;
	once = 1;
	/* Patch bpflet for current identifier. */
	insns[2] = (struct sock_filter)BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, HTONS(getpid()), 0, 1);
	if (setsockopt(raw_socket, SOL_SOCKET, SO_ATTACH_FILTER, &filter, sizeof(filter)))
		warn("failed to install socket filter");
}

static int	__set_cli(t_cli cli, int raw_socket, int level)
{
	int enable = 1;

	if (setsockopt(raw_socket, level, IP_TTL, &cli.ttl, sizeof(cli.ttl)) < 0)
		return (-1);
	if (setsockopt(raw_socket, level, IP_RECVTTL, &enable, sizeof(enable)) < 0)
		return (-1);
	// if (setsockopt(raw_socket, level, IP_RECVERR, &enable, sizeof(enable)) < 0)
		// return (-1);
	if (setsockopt(raw_socket, SOL_SOCKET, SO_RCVTIMEO, &cli.timeout, sizeof(cli.timeout)) < 0)
		return (-1);
	__set_filter(raw_socket);
	return (0);
}

int	create_icmp_socket(t_cli cli, struct addrinfo *address)
{
	int		raw_socket;

	raw_socket = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
	if (raw_socket == -1)
		return (-1);
	if (__set_cli(cli, raw_socket, GET_LEVEL(address->ai_family)) == -1)
		warn(strerror(errno));
	return (raw_socket);
}
