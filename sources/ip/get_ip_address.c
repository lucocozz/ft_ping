/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ip_address.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:31:34 by lucocozz          #+#    #+#             */
/*   Updated: 2022/12/30 12:38:53 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

char	*get_ip_address(struct addrinfo *address)
{
	char				*ip;
	size_t				size;
	struct sockaddr_in	*sockaddr = (struct sockaddr_in *)address->ai_addr;

	size = sizeof(char) * GET_ADDRLEN(address->ai_family);
	ip = malloc(size);
	if (ip == NULL)
		return (NULL);
	inet_ntop(address->ai_family, &sockaddr->sin_addr, ip, size);
	return (ip);
}
