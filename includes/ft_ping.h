/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:01:43 by user42            #+#    #+#             */
/*   Updated: 2022/12/07 01:36:46 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <signal.h>
# include <netdb.h>
# include <stdint.h>
# include <stdbool.h>
# include "libft.h"

# define EXIT_ERROR 2

# define MSG_MISSING_DEST "usage error: Destination address required"
# define MSG_INVALID_OPT "ping : invalid option -- "

# define PING_HELP							\
"Usage\n"									\
"  ft_ping [option] destination\n\n"		\
"Options:\n"								\
"<destionation>		dns or ip address\n"	\
"-h			print help and exit\n"			\
"-v			verbose output\n"

typedef struct s_option
{
	char	flag;
	bool	parameter;
	void	(*handler)(char *);
}	t_option;

void	exit_ping(int status, char *msg);
void	manage_options(int argc, char **argv);
void	handle_flag_h(char *parameter);

#endif
