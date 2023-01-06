/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ping_result.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:47:07 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/06 01:11:07 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	__print_timestamps(t_options options, t_recv_data data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (options.quiet != true && options.timestamps == true && data.error != ERR_TIMEOUT)
		printf("[%ld.%06ld] ", tv.tv_sec, tv.tv_usec);
}

void	print_ping_result(t_options options, t_recv_data data, int seq)
{
	__print_timestamps(options, data);
	if (options.quiet != true && data.error == ERR_TIMEOUT)
		printf("Request timed out.\n");
	else if (options.quiet != true && data.error == ERR_TTL_EXCEEPTED)
		printf("From %s: icmp_seq=%d Time to live exceeded\n", data.ptr_record, seq);
	else if (options.quiet != true)
	{
		if (is_ip_format(options.family, options.destination) == true) {
			printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.1f ms\n",
				data.bytes, data.from_addr, seq, data.ttl, data.time);
		} 
		else {
			printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%.1f ms\n",
				data.bytes, data.ptr_record, data.from_addr, seq, data.ttl, data.time);
		}
	}
}
