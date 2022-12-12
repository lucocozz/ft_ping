/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp_datagram.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:38:44 by user42            #+#    #+#             */
/*   Updated: 2022/12/12 19:46:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_icmp_datagram	create_icmp_datagram(size_t data_size)
{
	t_icmp_datagram	datagram;

	datagram.raw = malloc(sizeof(struct icmphdr) + data_size);
	if (datagram.raw == NULL)
		return (datagram);
	ft_bzero(datagram.raw, sizeof(struct icmphdr) + data_size);
	datagram.header = datagram.raw;
	datagram.data = datagram.raw + sizeof(struct icmphdr);
	return (datagram);
}

void	delete_icmp_datagram(t_icmp_datagram *datagram)
{
	free(datagram->raw);
	datagram->raw = NULL;
	datagram->header = NULL;
	datagram->data = NULL;
}
