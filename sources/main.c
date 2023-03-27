/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:39:11 by user42            #+#    #+#             */
/*   Updated: 2023/03/27 18:58:11 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_ping g_ping = {
	.running = true,
	.stats = {.min = __FLT_MAX__, .max = 0}
};

// static void	__check_broadcast(t_cli cli, struct addrinfo *address)
// {
// 	int	is_broadcast;

// 	is_broadcast = is_ip_broadcast(cli, address);
// 	if (is_broadcast == 1 && cli.broadcast == false) {
// 		freeaddrinfo(address);
// 		fatal(EXIT_ERROR, MSG_BROADCAST);
// 	}
// 	else if (is_broadcast == 1 && cli.broadcast == true)
// 		warn(MSG_WARN_BROADCAST);
// 	else if (is_broadcast == -1)
// 		fatal(EXIT_FAILURE, strerror(errno));
// }

int main(int argc, char **argv)
{
	int				socket;
	int				result;
	t_cli		cli;
	struct addrinfo	*address;

	cli = get_cli(argc, argv);
	address = resolve_service(cli.destination, cli.family);
	// __check_broadcast(cli, address);
	// printf("mask: %s\n", get_ip_netmask(cli.destination));
	socket = create_icmp_socket(cli, address);
	if (socket == -1) {
		cleanup(-1, address);
		fatal(EXIT_FAILURE, strerror(errno));
	}
	set_signals_handlers();
	set_alarm(cli);
	result = ping(cli, address, socket);
	cleanup(socket, address);
	if (result == ERR_UNDEFINED)
		fatal(EXIT_FAILURE, strerror(errno));
	return (EXIT_SUCCESS);
}
