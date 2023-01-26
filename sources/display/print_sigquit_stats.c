/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sigquit_stats.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:40:55 by user42            #+#    #+#             */
/*   Updated: 2023/01/26 14:59:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_sigquit_stats(int signum)
{
	t_rtt_stats	stats = g_ping.stats;

	(void)signum;
	printf("\r%d/%d packets, %d%% loss, min/avg/ewma/max = %.3f/%.3f/%.3f/%.3f ms\n",
	stats.received, stats.transmitted, stats.loss, stats.min, stats.avg, stats.ewma, stats.max);
}
