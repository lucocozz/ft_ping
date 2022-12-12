/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:39:11 by user42            #+#    #+#             */
/*   Updated: 2022/12/12 20:57:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	init_socket(t_options options)
{
	int		raw_socket;
	int		type;
	uid_t	uid = getuid();

	type = (uid == 0 ? SOCK_RAW : SOCK_DGRAM);
	raw_socket = socket(PF_INET, type, IPPROTO_ICMP);
	if (raw_socket == -1)
		return (-1);
	if (setuid(uid) == -1)
		return (-1);
	(void)options;
	// setsockopt(raw_socket, );
	return (raw_socket);
}

int	main(int argc, char **argv)
{
	t_options		options;
	int				raw_socket;

	if (argc == 1)
		fatal(EXIT_ERROR, MSG_MISSING_DEST);
	options = manage_options(argc, argv);
	if (options.destination == NULL)
		fatal(EXIT_FAILURE, MSG_USAGE_ERR);
	raw_socket = init_socket(options);
	if (raw_socket == -1)
		fatal(EXIT_FAILURE, strerror(errno));
	close(raw_socket);
	return (EXIT_SUCCESS);
}
