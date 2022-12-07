/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:39:11 by user42            #+#    #+#             */
/*   Updated: 2022/12/07 19:09:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	exit_ping(int status, char *msg)
{
	int	fd = status == EXIT_SUCCESS ? STDOUT_FILENO : STDERR_FILENO;

	if (msg != NULL)
		dprintf(fd, "ft_ping: %s\n", msg);
	exit(status);
}

int	main(int argc, char **argv)
{
	t_options	options;

	if (argc == 1)
		exit_ping(EXIT_ERROR, MSG_MISSING_DEST);
	options = manage_options(argc, argv);
	printf("destination = %s\n", options.destination);
	return (EXIT_SUCCESS);
}
