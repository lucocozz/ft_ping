/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:06:25 by lucocozz          #+#    #+#             */
/*   Updated: 2022/12/29 16:06:36 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	cleanup(int socket, struct addrinfo *address)
{
	if (socket != -1)
		close(socket);
	if (address != NULL)
		freeaddrinfo(address);
}
