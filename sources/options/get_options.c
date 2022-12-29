/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:52:36 by lucocozz          #+#    #+#             */
/*   Updated: 2022/12/29 15:53:14 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_options	get_options(int argc, char **argv)
{
	t_options	options;

	if (argc == 1)
		fatal(EXIT_ERROR, MSG_MISSING_DEST);
	options = parse_options(argc, argv);
	if (options.destination == NULL)
		fatal(EXIT_FAILURE, MSG_USAGE_ERR);
	return (options);
}
