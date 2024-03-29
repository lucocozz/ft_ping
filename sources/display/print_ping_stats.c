/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ping_stats.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 02:08:01 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/27 18:58:32 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_ping_stats(t_cli cli)
{
	t_rtt_stats stats = g_ping.stats;

	printf("\n--- %s ping statistics ---\n", cli.destination);
	if (stats.error > 0) {
		printf("%d packets transmitted, %d received, +%d errors, %d%% packet loss, time %dms\n",
			stats.transmitted, stats.received, stats.error, stats.loss, stats.time);
	}
	else {
		printf("%d packets transmitted, %d received, %d%% packet loss, time %dms\n",
			stats.transmitted, stats.received, stats.loss, stats.time);
	}
	printf("rtt min/avg/max/mdev %.3f/%.3f/%.3f/%.3f ms\n", stats.min, stats.avg,
		stats.max, stats.mdev);
}
