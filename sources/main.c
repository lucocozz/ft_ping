/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:39:11 by user42            #+#    #+#             */
/*   Updated: 2023/01/09 17:10:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

bool g_running = true;

static void	__check_broadcast(t_options options, struct addrinfo *address)
{
	int	is_broadcast;

	is_broadcast = is_ip_broadcast(options, address);
	if (is_broadcast == 1 && options.broadcast == false) {
		freeaddrinfo(address);
		fatal(EXIT_ERROR, MSG_BROADCAST);
	}
	else if (is_broadcast == 1 && options.broadcast == true)
		warn(MSG_WARN_BROADCAST);
	else if (is_broadcast == -1)
		fatal(EXIT_FAILURE, strerror(errno));
}

int main(int argc, char **argv)
{
	int				socket;
	int				result;
	t_options		options;
	struct addrinfo	*address;

	options = get_options(argc, argv);
	address = resolve_service(options.destination, options.family);
	__check_broadcast(options, address);
	socket = create_icmp_socket(options, address);
	if (socket == -1) {
		cleanup(-1, address);
		fatal(EXIT_FAILURE, strerror(errno));
	}
	set_signals_handlers();
	set_alarm(options);
	result = ping(options, address, socket);
	cleanup(socket, address);
	if (result == ERR_UNDEFINED)
		fatal(EXIT_FAILURE, strerror(errno));
	return (EXIT_SUCCESS);
}
