/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:01:43 by user42            #+#    #+#             */
/*   Updated: 2023/01/20 01:27:29 by user42           ###   ########.fr       */
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
# include <ifaddrs.h>
# include "libft.h"

# define IMPLEMENT_PING

# define GET_LEVEL(family) (family == PF_INET ? IPPROTO_IP : IPPROTO_IPV6)
# define GET_ADDRLEN(family) (family == PF_INET ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN)

# define EXIT_ERROR 2
# define MIN_INTERVAL 0.002
# define MSG_BUFFER_SIZE 2048
# define PTR_RECORD_SIZE 255
# define NETMASK_A "255.0.0.0"
# define NETMASK_B "255.255.0.0"
# define NETMASK_C "255.255.255.0"
# define NETMASK_D "255.255.255.255"

# define DFT_COUNT -1
# define DFT_VERBOSE false
# define DFT_DESTINATION NULL
# define DFT_INTERVAL 1000000
# define DFT_TIMESTAMPS false
# define DFT_TIMEOUT 4
# define DFT_QUIET false
# define DFT_SIZE 56
# define DFT_TTL 64
# define DFT_WAIT 0
# define DFT_FAMILY PF_INET
# define DFT_BROADCAST false
# define DFT_NO_DNS false

# define NOERROR 0
# define INTERRUPTED -2
# define ERR_UNDEFINED -1
# define ERR_TTL_EXCEEPTED 1
# define ERR_TIMEOUT 2
# define ERR_NET_UNREACHABLE 3


# define MSG_NAME "ft_ping: "
# define MSG_FATAL "Fatal error"
# define MSG_MISSING_DEST "usage error: Destination address required"
# define MSG_INVALID_OPT "ft_ping: invalid option -- "
# define MSG_REQUIRED_ARG "ft_ping: option requires an argument -- "
# define MSG_INVALID_ARG "invalid argument:"
# define MSG_FLOOD "cannot flood; minimal interval allowed for user is 2ms"
# define MSG_USAGE_ERR "usage error: Destination address required"
# define MSG_BROADCAST "Do you want to ping broadcast? Then -b. If not, check your local firewall rules."
# define MSG_WARN_BROADCAST "pinging broadcast address"
# define MSG_OPT_GARBAGE "ft_ping: option argument contains garbage"
# define MSG_WARN_FATAL "ft_ping: this will become fatal error in the future"
# define MSG_BAD_LINGER_TIME "ft_ping: bad linger time"

# define PING_HELP												\
"Usage\n"														\
"  ft_ping [option] <destination>\n\n"							\
"Options:\n"													\
"<destionation>	dns or ip address\n"							\
"-c <count>	stop after <count> replies\n"						\
"-D		print timestamps\n"										\
"-h		print help and exit\n"									\
"-i <interval>	seconds between sending each packet\n"			\
"-n		no dns name resolution\n"								\
"-q		quiet output\n"											\
"-s <size>	use <size> as number of data bytes to be sent\n"	\
"-t <ttl>	define time to live\n"								\
"-v		verbose output\n"										\
"-w <deadline>	reply wait <deadline> in seconds\n"				\
"-W <timeout>	Time to wait for response\n"					\
"\nIPv4 options:\n"												\
"  -4		Use IPv4\n"											\
"\nIPv6 options:\n"												\
"  -6		Use IPv6\n"

typedef struct s_options
{
	char			*destination;
	int				interval;
	struct timeval	timeout;
	bool			timestamps;
	bool			verbose;
	bool			broadcast;
	bool			no_dns;
	int				family;
	long long		count;
	bool			quiet;
	int				size;
	int				wait;
	short			ttl;
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
	size_t			size;
	size_t			total;
} t_icmp_datagram;

typedef struct s_recv_data
{
	int		ttl;
	int		bytes;
	char	ptr_record[PTR_RECORD_SIZE];
	char	from_addr[48];
	float	time;
	short	error;
}	t_recv_data;

typedef struct s_rtt_stats
{
	uint		transmitted;
	uint		received;
	uint		error;
	__u_short	loss;
	uint		time;
	float		min;
	float		max;
	float		avg;
	float		mdev;
}	t_rtt_stats;

extern bool g_running;

/* system */
void	warn(const char *msg);
void	fatal(short status, const char *msg);
void	verbose(bool is_active, const char *str);
void	set_signals_handlers(void);
void	handle_signals(int signum);
void	set_signals_handlers(void);
void	set_alarm(t_options options);
void	cleanup(int socket, struct addrinfo *address);

/* icmp */
int				create_icmp_socket(t_options options, struct addrinfo *address);
t_icmp_datagram	create_icmp_datagram(size_t data_size, uint8_t type, uint8_t code);
void			delete_icmp_datagram(t_icmp_datagram *datagram);
int				send_datagram(int socket, t_icmp_datagram datagram, struct addrinfo *address);
t_recv_data		recv_datagram(t_options options, int socket, int family);

/* ip */
char			*get_ip_address(struct addrinfo *address);
struct addrinfo	*resolve_service(const char *service, int family);
uint16_t		checksum(uint16_t *addr, size_t len);
bool			is_ip_format(int family, char *ip);
int				is_ip_broadcast(t_options options, struct addrinfo *address);
char			*get_ip_netmask(char *ip_address);

/* utils */
float	get_elapsed_time(struct timeval start, struct timeval end);

/* ping */
int			ping(t_options options, struct addrinfo *address, int socket);
t_recv_data	ping_datagram(t_options options, int socket, t_icmp_datagram datagram,
				struct addrinfo *address);
void		set_ping_stats(t_rtt_stats *stats, t_recv_data result);

/* display */
void	print_ping_header(t_options options, char *ip, t_icmp_datagram datagram);
void	print_ping_result(t_options options, t_recv_data data, int seq);
void	print_ping_stats(t_options options, t_rtt_stats stats);

/* options */
t_options	get_options(int argc, char **argv);
t_options	parse_options(int argc, char **argv);

void	handle_flag_h(t_options *data, char *argument);
void	handle_flag_v(t_options *data, char *argument);
void	handle_flag_c(t_options *data, char *argument);
void	handle_flag_i(t_options *data, char *argument);
void	handle_flag_D(t_options *data, char *argument);
void	handle_flag_q(t_options *data, char *argument);
void	handle_flag_s(t_options *data, char *argument);
void	handle_flag_t(t_options *data, char *argument);
void	handle_flag_w(t_options *data, char *argument);
void	handle_flag_W(t_options *data, char *argument);
void	handle_flag_4(t_options *data, char *argument);
void	handle_flag_6(t_options *data, char *argument);
void	handle_flag_b(t_options *data, char *argument);
void	handle_flag_n(t_options *data, char *argument);

#endif
