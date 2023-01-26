/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:28:15 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/26 14:41:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	set_signals_handlers(void)
{
	signal(SIGALRM, &handle_signals);
	signal(SIGINT, &handle_signals);
	signal(SIGQUIT, &print_sigquit_stats);
}

void	handle_signals(int signum)
{
	(void)signum;
	g_ping.running = false;
}
