/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:26:22 by user42            #+#    #+#             */
/*   Updated: 2022/12/07 01:07:16 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	handle_flag_h(char *parameter)
{
	(void)parameter;
	printf(PING_HELP);
	exit(EXIT_SUCCESS);
}