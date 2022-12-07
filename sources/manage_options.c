/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:30:35 by user42            #+#    #+#             */
/*   Updated: 2022/12/07 20:48:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int	__check_flag(t_options *data, char flag, char *argument)
{
	uint						i = 0;
	static const t_option_table	options[] = {
		{.flag = 'h', .handler = &handle_flag_h, .has_argument = false},
		{.flag = 'v', .handler = &handle_flag_v, .has_argument = false},
		{0}
	};
	
	for (i = 0; options[i].flag != 0; ++i) {
		if (flag == options[i].flag) {
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

	options.verbose = false;
	options.destination = NULL;
	return (options);
}

t_options	manage_options(int argc, char **argv)
{
	char		*flag;
	char		*argument;
	t_options	options = __init_options();

	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-' && argv[i][1] != '\0')
		{
			flag = &argv[i][1];
			while (*flag != '\0')
			{
				if (*(flag + 1) != '\0')
					argument = (flag + 1);
				else if (i < argc)
					argument = argv[i];
				else
					argument = NULL;
				i += __check_flag(&options, *flag, argument);
				++flag;
			}
		}
		else
			options.destination = argv[i];
	}
	return (options);
}
