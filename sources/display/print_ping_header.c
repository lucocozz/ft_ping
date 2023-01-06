/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ping_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:45:07 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/06 20:56:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_ping_header(t_options options, char *ip, t_icmp_datagram datagram)
{
	printf("FT_PING %s (%s) %zu(%lu) bytes of data.\n", options.destination, ip,
		datagram.size, datagram.total);
}
