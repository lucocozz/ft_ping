/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ping_stats.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 02:19:54 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/27 19:15:11 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	set_ping_stats(t_querie querie)
{
	const float		alpha = 0.1;
	static float	mean = 0.0;
	static float	variance = 0.0;
	t_rtt_stats		*stats = &g_ping.stats;

	stats->transmitted++;
	if (querie.error == NOERROR)
		stats->received++;
	if (querie.error != NOERROR && querie.error != ERR_TIMEOUT && querie.error != INTERRUPTED)
		stats->error++;
	stats->loss = (stats->transmitted - stats->received) / stats->transmitted * 100;
	stats->time += (querie.time * 100);
	if (querie.time < stats->min)
		stats->min = querie.time;
	if (querie.time > stats->max)
		stats->max = querie.time;
	mean += querie.time;
	variance += (querie.time * querie.time);
	stats->avg = mean / stats->received;
	stats->mdev = ft_sqrt((variance / stats->received) - (stats->avg * stats->avg));	
	if (stats->ewma == 0)
		stats->ewma = querie.time;
	else
		stats->ewma = (alpha * querie.time) + ((1 - alpha) * stats->ewma);
}
