/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:39:11 by user42            #+#    #+#             */
/*   Updated: 2022/12/06 22:16:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	exit_ping(int status, char *msg)
{
	int	fd = status == EXIT_SUCCESS ? STDOUT_FILENO : STDERR_FILENO;

	if (msg != NULL)
		dprintf(fd, "ping: %s", msg);
	exit(status);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		exit_ping(EXIT_ERROR, "usage error: Destination address required\n");
	handle_options(argc, argv);

	return (EXIT_SUCCESS);
}
