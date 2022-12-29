/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:39:11 by user42            #+#    #+#             */
/*   Updated: 2022/12/29 16:48:09 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

bool g_running = true;

int main(int argc, char **argv)
{
	int				socket;
	int				result;
	t_options		options;
	struct addrinfo	*address;

	options = get_options(argc, argv);
	address = resolve_service(options.destination, options.family);
	socket = create_icmp_socket(options, address);
	if (socket == -1) {
		cleanup(-1, address);
		fatal(EXIT_FAILURE, strerror(errno));
	}
	set_signals_handlers();
	set_alarm(options);
	result = ping(options, address, socket);
	cleanup(socket, address);
	if (result == -1)
		fatal(EXIT_FAILURE, MSG_FATAL);
	return (EXIT_SUCCESS);
}
