/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:30:35 by user42            #+#    #+#             */
/*   Updated: 2022/12/29 15:50:53 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int	__check_flag(t_options *data, char flag, char *argument)
{
	uint						i = 0;
	static const t_option_table	options[] = {
		{.flag = 'h', .handler = &handle_flag_h, .has_argument = false},
		{.flag = 'v', .handler = &handle_flag_v, .has_argument = false},
		{.flag = 'D', .handler = &handle_flag_D, .has_argument = false},
		{.flag = 'q', .handler = &handle_flag_q, .has_argument = false},
		{.flag = 'c', .handler = &handle_flag_c, .has_argument = true},
		{.flag = 'i', .handler = &handle_flag_i, .has_argument = true},
		{.flag = 's', .handler = &handle_flag_s, .has_argument = true},
		{.flag = 't', .handler = &handle_flag_t, .has_argument = true},
		{.flag = 'w', .handler = &handle_flag_w, .has_argument = true},
		{0}
	};
	
	for (i = 0; options[i].flag != 0; ++i) {
		if (flag == options[i].flag) {
			if (options[i].has_argument == true && argument == NULL) {
				printf("%s'%c'\n\n", MSG_REQUIRED_ARG, flag);
				handle_flag_h(NULL, NULL);
			}
			options[i].handler(data, options[i].has_argument == true ? argument : NULL);
			break ;
		}
	}
	if (options[i].flag == 0) {
		printf("%s'%c'\n\n", MSG_INVALID_OPT, flag);
		handle_flag_h(NULL, NULL);
	}
	return (options[i].has_argument);
}

static t_options	__init_options(void)
{
	t_options	options;

	options.count = DFT_COUNT;
	options.verbose = DFT_VERBOSE;
	options.destination = DFT_DESTINATION;
	options.interval = DFT_INTERVAL;
	options.timestamps = DFT_TIMESTAMPS;
	options.quiet = DFT_QUIET;
	options.size = DFT_SIZE;
	options.ttl = DFT_TTL;
	options.wait = DFT_WAIT;
	options.family = DFT_FAMILY;
	return (options);
}

t_options	parse_options(int argc, char **argv)
{
	char		*flag;
	t_options	options = __init_options();

	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-' && argv[i][1] != '\0')
		{
			flag = &argv[i][1];
			while (*flag != '\0')
			{
				if (*(flag + 1) != '\0')
					__check_flag(&options, *flag, (flag + 1));
				else if (i < argc - 1)
					i += __check_flag(&options, *flag, argv[i + 1]);
				else
					__check_flag(&options, *flag, NULL);
				++flag;
			}
		}
		else
			options.destination = argv[i];
	}
	return (options);
}
