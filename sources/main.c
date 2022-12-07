/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:39:11 by user42            #+#    #+#             */
/*   Updated: 2022/12/07 22:26:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	fatal(short status, const char *msg)
{
	if (msg != NULL)
		dprintf(STDERR_FILENO, "ft_ping: %s\n", msg);
	exit(status);
}

void	warn(const char *msg)
{
	if (msg != NULL)
		dprintf(STDERR_FILENO, "ft_ping: %s\n", msg);
}

int	main(int argc, char **argv)
{
	t_options	options;
	int			icmp_socket;
	struct icmphdr	icmp_header;

	if (argc == 1)
		fatal(EXIT_ERROR, MSG_MISSING_DEST);
	options = manage_options(argc, argv);
	icmp_socket = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	icmp_header.type = ICMP_ECHO;
	return (EXIT_SUCCESS);
}
