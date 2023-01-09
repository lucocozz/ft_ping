/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ip_broadcast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:15:04 by user42            #+#    #+#             */
/*   Updated: 2023/01/09 17:13:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	is_ip_broadcast(t_options options, struct addrinfo *address)
{
	int	probe_fd;

	probe_fd = socket(options.family, SOCK_DGRAM, 0);
	if (probe_fd == -1)
		return (-1);
	if (connect(probe_fd, (struct sockaddr *)address, sizeof(*address)) == -1) {
		close(probe_fd);
		if (errno == EACCES)
			return (1);
		return (-1);
	}
	close(probe_fd);
	return (0);
}
