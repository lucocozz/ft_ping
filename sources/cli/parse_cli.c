/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cli.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:30:35 by user42            #+#    #+#             */
/*   Updated: 2023/02/22 20:09:32 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int	__check_flag(t_cli *cli, char flag, char *argument)
{
	uint						i = 0;
	static const t_options	options[] = {
		{.flag = 'h', .handler = &handle_flag_h, .has_argument = false},
		{.flag = 'v', .handler = &handle_flag_v, .has_argument = false},
		{.flag = 'D', .handler = &handle_flag_D, .has_argument = false},
		{.flag = 'q', .handler = &handle_flag_q, .has_argument = false},
		{.flag = '4', .handler = &handle_flag_4, .has_argument = false},
		{.flag = '6', .handler = &handle_flag_6, .has_argument = false},
		{.flag = 'b', .handler = &handle_flag_b, .has_argument = false},
		{.flag = 'n', .handler = &handle_flag_n, .has_argument = false},
		{.flag = 'c', .handler = &handle_flag_c, .has_argument = true},
		{.flag = 'i', .handler = &handle_flag_i, .has_argument = true},
		{.flag = 's', .handler = &handle_flag_s, .has_argument = true},
		{.flag = 't', .handler = &handle_flag_t, .has_argument = true},
		{.flag = 'w', .handler = &handle_flag_w, .has_argument = true},
		{.flag = 'W', .handler = &handle_flag_W, .has_argument = true},
		{0}
	};

	for (i = 0; options[i].flag != 0; ++i) {
		if (flag == options[i].flag) {
			if (options[i].has_argument == true && argument == NULL) {
				printf("%s'%c'\n\n", MSG_REQUIRED_ARG, flag);
				handle_flag_h(NULL, NULL);
			}
			options[i].handler(cli, argument);
			break ;
		}
	}
	if (options[i].flag == 0) {
		printf("%s'%c'\n\n", MSG_INVALID_OPT, flag);
		handle_flag_h(NULL, NULL);
	}
	return (options[i].has_argument);
}

static t_cli	__init_cli(void)
{
	t_cli	cli;

	cli.count = DFT_COUNT;
	cli.verbose = DFT_VERBOSE;
	cli.destination = DFT_DESTINATION;
	cli.interval = DFT_INTERVAL;
	cli.timestamps = DFT_TIMESTAMPS;
	cli.timeout = (struct timeval){.tv_sec = DFT_TIMEOUT, .tv_usec = 0};
	cli.quiet = DFT_QUIET;
	cli.size = DFT_SIZE;
	cli.ttl = DFT_TTL;
	cli.wait = DFT_WAIT;
	cli.family = DFT_FAMILY;
	cli.broadcast = DFT_BROADCAST;
	cli.no_dns = DFT_NO_DNS;
	return (cli);
}

t_cli	parse_cli(int argc, char **argv)
{
	char		*flag;
	t_cli	cli = __init_cli();

	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-' && argv[i][1] != '\0')
		{
			flag = &argv[i][1];
			while (*flag != '\0')
			{
				if (*(flag + 1) != '\0') {
					__check_flag(&cli, *flag, (flag + 1));
					break ;
				}
				else if (i < argc - 1)
					i += __check_flag(&cli, *flag, argv[i + 1]);
				else
					__check_flag(&cli, *flag, NULL);
				++flag;
			}
		}
		else
			cli.destination = argv[i];
	}
	return (cli);
}
