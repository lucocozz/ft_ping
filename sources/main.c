/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:39:11 by user42            #+#    #+#             */
/*   Updated: 2022/12/14 17:01:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	init_socket(t_options options)
{
	int		raw_socket;

	raw_socket = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (raw_socket == -1)
		return (-1);
	(void)options;
	// setsockopt(raw_socket, );
	return (raw_socket);
}

void	resolve_service_name(const char *service_name, struct addrinfo **peer_address)
{
	struct addrinfo	hints = {0};
	char			msg[256] = {0};

	hints.ai_socktype = SOCK_RAW;
	if (getaddrinfo(service_name, NULL, &hints, peer_address) < 0) {
		sprintf(msg, "%s: Name or service not known", service_name);
		fatal(EXIT_FAILURE, msg);
	}
}

int	main(int argc, char **argv)
{
	t_options		options;
	int				raw_socket;
	struct addrinfo	*peer_address;

	if (argc == 1)
		fatal(EXIT_ERROR, MSG_MISSING_DEST);
	options = manage_options(argc, argv);
	if (options.destination == NULL)
		fatal(EXIT_FAILURE, MSG_USAGE_ERR);
	raw_socket = init_socket(options);
	if (raw_socket == -1)
		fatal(EXIT_FAILURE, strerror(errno));
	resolve_service_name(options.destination, &peer_address);
	freeaddrinfo(peer_address);
	close(raw_socket);
	return (EXIT_SUCCESS);
}
