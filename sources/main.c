/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:39:11 by user42            #+#    #+#             */
/*   Updated: 2022/12/07 01:36:04 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	exit_ping(int status, char *msg)
{
	int	fd = status == EXIT_SUCCESS ? STDOUT_FILENO : STDERR_FILENO;

	if (msg != NULL)
		dprintf(fd, "ping: %s\n", msg);
	exit(status);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		exit_ping(EXIT_ERROR, MSG_MISSING_DEST);
	manage_options(argc, argv);

	return (EXIT_SUCCESS);
}
