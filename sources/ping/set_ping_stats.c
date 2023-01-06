/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ping_stats.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 02:19:54 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/06 12:24:59 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	set_ping_stats(t_rtt_stats *stats, t_recv_data result)
{
	static float	mean = 0.0;
	static float	variance = 0.0;

	stats->transmitted++;
	if (result.error == NOERROR)
		stats->received++;
	if (result.error != NOERROR && result.error != ERR_TIMEOUT)
		stats->error++;
	stats->loss = (stats->transmitted - stats->received) / stats->transmitted * 100;
	stats->time += (result.time * 100);
	if (result.time < stats->min)
		stats->min = result.time;
	if (result.time > stats->max)
		stats->max = result.time;
	mean += result.time;
	variance += (result.time * result.time);
	stats->avg = mean / stats->transmitted;
	stats->mdev = ft_sqrt((variance / stats->transmitted) - (stats->avg * stats->avg));	
}
