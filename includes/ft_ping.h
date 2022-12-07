/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:01:43 by user42            #+#    #+#             */
/*   Updated: 2022/12/07 19:52:45 by user42           ###   ########.fr       */
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
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include "libft.h"

# define EXIT_ERROR 2

# define MSG_MISSING_DEST "usage error: Destination address required"
# define MSG_INVALID_OPT "ft_ping: invalid option -- "

# define PING_HELP							\
"Usage\n"									\
"  ft_ping [option] <destination>\n\n"		\
"Options:\n"								\
"<destionation>		dns or ip address\n"	\
"-h			print help and exit\n"			\
"-v			verbose output\n"

typedef struct s_options
{
	char	*destination;
	bool	verbose;
}	t_options;

typedef struct s_option_table
{
	char	flag;
	bool	has_argument;
	void	(*handler)(t_options *, char *);
}	t_option_table;

void		exit_ping(int status, char *msg);
t_options	manage_options(int argc, char **argv);
void		verbose(bool is_active, const char *str);

void		handle_flag_h(t_options *data, char *argument);
void		handle_flag_v(t_options *data, char *argument);

#endif
