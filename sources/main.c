/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:39:11 by user42            #+#    #+#             */
/*   Updated: 2023/01/05 16:52:34 by user42           ###   ########.fr       */
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
	if (result == ERR_UNDEFINED)
		fatal(EXIT_FAILURE, strerror(errno));
	return (EXIT_SUCCESS);
}
