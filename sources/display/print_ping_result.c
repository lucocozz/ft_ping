/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ping_result.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:47:07 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/05 19:15:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_ping_result(t_options options, t_recv_data data, char *ip, int seq)
{
	if (options.quiet != true && data.error == ERR_TIMEOUT)
		printf("Request timed out.\n");
	else if (options.quiet != true && data.error == ERR_TTL_EXCEEPTED)
		printf("From %s: icmp_seq=%d Time to live exceeded\n", data.from_addr, seq);
	else if (options.quiet != true) {
		printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.1f ms\n",
			data.bytes, ip, seq, data.ttl, data.time);
	}
}
