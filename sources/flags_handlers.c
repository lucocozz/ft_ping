/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:26:22 by user42            #+#    #+#             */
/*   Updated: 2022/12/07 19:09:11 by user42           ###   ########.fr       */
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