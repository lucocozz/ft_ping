/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ping_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:45:07 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/27 18:58:14 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_ping_header(t_cli cli, char *ip, t_icmp_datagram datagram)
{
	printf("FT_PING %s (%s) %zu(%lu) bytes of data.\n", cli.destination, ip,
		datagram.size, datagram.total + sizeof(struct iphdr));
}
