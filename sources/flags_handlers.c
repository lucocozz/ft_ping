/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:26:22 by user42            #+#    #+#             */
/*   Updated: 2022/12/09 18:09:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	handle_flag_h(t_options *data, char *argument)
{
	(void)(data && argument);
	printf(PING_HELP);
	exit(EXIT_SUCCESS);
}

void	handle_flag_v(t_options *data, char *argument)
{
	(void)argument;
	data->verbose = true;
}

void	handle_flag_c(t_options *data, char *argument)
{
	//TODO: implement c flag
	data->count;
}

void	handle_flag_i(t_options *data, char *argument)
{
	//TODO: implement i flag
	data->interval;
}

void	handle_flag_D(t_options *data, char *argument)
{
	(void)argument;
	data->datetime = true;
}

void	handle_flag_q(t_options *data, char *argument)
{
	(void)argument;
	data->quiet = true;
}

void	handle_flag_s(t_options *data, char *argument)
{
	//TODO: implement s flag
	data->size;
}

void	handle_flag_t(t_options *data, char *argument)
{
	//TODO: implement t flag
	data->ttl;
}

void	handle_flag_w(t_options *data, char *argument)
{
	//TODO: implement w flag
	data->wait;
}