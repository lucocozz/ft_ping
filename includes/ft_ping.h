/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:01:43 by user42            #+#    #+#             */
/*   Updated: 2022/12/13 15:32:38 by user42           ###   ########.fr       */
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
# include <linux/tcp.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

# define IMPLEMENT_PING

# define EXIT_ERROR 2
# define MIN_INTERVAL 0.002

# define MSG_NAME "ft_ping: "
# define MSG_MISSING_DEST "usage error: Destination address required"
# define MSG_INVALID_OPT "ft_ping: invalid option -- "
# define MSG_REQUIRED_ARG "ft_ping: option requires an argument -- "
# define MSG_INVALID_ARG "invalid argument:"
# define MSG_FLOOD "cannot flood; minimal interval allowed for user is 2ms"
# define MSG_USAGE_ERR "usage error: Destination address required"

# define DFT_COUNT -1
# define DFT_VERBOSE false
# define DFT_DESTINATION NULL
# define DFT_INTERVAL 1000
# define DFT_TIMESTAMPS false
# define DFT_QUIET false
# define DFT_SIZE 56
# define DFT_TTL 255
# define DFT_WAIT -1

# define PING_HELP												\
"Usage\n"														\
"  ft_ping [option] <destination>\n\n"							\
"Options:\n"													\
"<destionation>	dns or ip address\n"							\
"-h		print help and exit\n"									\
"-v		verbose output\n"										\
"-D		print timestamps\n"										\
"-q		quiet output\n"											\
"-c <count>	stop after <count> replies\n"						\
"-i <interval>	seconds between sending each packet\n"			\
"-s <size>	use <size> as number of data bytes to be sent\n"	\
"-t <ttl>	define time to live\n"								\
"-w <deadline>	reply wait <deadline> in seconds\n"

typedef struct s_options
{
	char		*destination;
	int			interval;
	bool		timestamps;
	bool		verbose;
	long long	count;
	bool		quiet;
	int			size;
	int			wait;
	short		ttl;
}	t_options;

typedef struct s_option_table
{
	char	flag;
	bool	has_argument;
	void	(*handler)(t_options *, char *);
}	t_option_table;

typedef struct s_icmp_datagram
{
	struct icmphdr	*header;
	void			*raw;
	char			*data;
} t_icmp_datagram;


void			warn(const char *msg);
void			fatal(short status, const char *msg);
void			verbose(bool is_active, const char *str);
t_options		manage_options(int argc, char **argv);
t_icmp_datagram	create_icmp_datagram(size_t data_size);
void			delete_icmp_datagram(t_icmp_datagram *datagram);

void	handle_flag_h(t_options *data, char *argument);
void	handle_flag_v(t_options *data, char *argument);
void	handle_flag_c(t_options *data, char *argument);
void	handle_flag_i(t_options *data, char *argument);
void	handle_flag_D(t_options *data, char *argument);
void	handle_flag_q(t_options *data, char *argument);
void	handle_flag_s(t_options *data, char *argument);
void	handle_flag_t(t_options *data, char *argument);
void	handle_flag_w(t_options *data, char *argument);

#endif
