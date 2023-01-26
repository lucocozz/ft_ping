/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ping_stats.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 02:19:54 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/26 15:12:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	set_ping_stats(t_recv_data result)
{
	const float		alpha = 0.1;
	static float	mean = 0.0;
	static float	variance = 0.0;
	t_rtt_stats		*stats = &g_ping.stats;

	stats->transmitted++;
	if (result.error == NOERROR)
		stats->received++;
	if (result.error != NOERROR && result.error != ERR_TIMEOUT && result.error != INTERRUPTED)
		stats->error++;
	stats->loss = (stats->transmitted - stats->received) / stats->transmitted * 100;
	stats->time += (result.time * 100);
	if (result.time < stats->min)
		stats->min = result.time;
	if (result.time > stats->max)
		stats->max = result.time;
	mean += result.time;
	variance += (result.time * result.time);
	stats->avg = mean / stats->received;
	stats->mdev = ft_sqrt((variance / stats->received) - (stats->avg * stats->avg));	
	if (stats->ewma == 0)
		stats->ewma = result.time;
	else
		stats->ewma = (alpha * result.time) + ((1 - alpha) * stats->ewma);
}
