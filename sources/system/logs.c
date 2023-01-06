/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:40:56 by user42            #+#    #+#             */
/*   Updated: 2023/01/06 20:55:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	fatal(short status, const char *msg)
{
	if (msg != NULL)
		dprintf(STDERR_FILENO, "%s%s\n", MSG_NAME, msg);
	exit(status);
}

void	warn(const char *msg)
{
	if (msg != NULL)
		dprintf(STDERR_FILENO, "WARNING: %s\n", msg);
}

void	verbose(bool is_active, const char *str)
{
	if (is_active == true)
		printf("%s%s", MSG_NAME, str);
}
