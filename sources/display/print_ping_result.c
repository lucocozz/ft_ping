/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ping_result.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:47:07 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/27 19:14:00 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	__print_timestamps(t_cli cli, t_querie querie)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) >= 0) {
		if (cli.quiet != true && cli.timestamps == true && querie.error != ERR_TIMEOUT)
			printf("[%ld.%06ld] ", tv.tv_sec, tv.tv_usec);
	}
}

void	print_ping_result(t_cli cli, t_querie querie, int seq)
{
	__print_timestamps(cli, querie);
	if (cli.quiet != true && cli.verbose == true && querie.error == ERR_TIMEOUT)
		printf("Request timed out.\n");
	else if (cli.quiet != true && querie.error == ERR_NET_UNREACHABLE)
		printf("From %s: icmp_seq=%d Destination Net Unreachable\n", querie.from_addr, seq);
	else if (cli.quiet != true && querie.error == ERR_TTL_EXCEEPTED)
		printf("From %s: icmp_seq=%d Time to live exceeded\n", querie.from_addr, seq);
	else if (cli.quiet != true && querie.error == NOERROR)
	{
		if (is_ip_format(cli.family, cli.destination) == true || cli.no_dns == true) {
			printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.2f ms\n",
				querie.bytes, querie.from_addr, seq, querie.ttl, querie.time);
		} 
		else {
			printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%.2f ms\n",
				querie.bytes, querie.ptr_record, querie.from_addr, seq, querie.ttl, querie.time);
		}
	}
}
