/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:28:15 by lucocozz          #+#    #+#             */
/*   Updated: 2022/12/29 15:49:40 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	set_signals_handlers(void)
{
	signal(SIGALRM, &handle_signals);
	signal(SIGINT, &handle_signals);
}

void	handle_signals(int signum)
{
	(void)signum;
	g_running = false;
}
