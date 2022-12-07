/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:30:35 by user42            #+#    #+#             */
/*   Updated: 2022/12/07 19:20:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	__check_flag(t_options *data, char flag, char *argument)
{
	uint						i = 0;
	static const t_option_table	options[] = {
		{.flag = 'h', .handler = &handle_flag_h, .has_argument = false},
		{.flag = 'v', .handler = &handle_flag_v, .has_argument = false},
		{0}
	};
	
	for (i = 0; options[i].flag != 0; ++i) {
		if (flag == options[i].flag) {
			options[i].handler(data, options[i].has_argument == false ? NULL : argument);
			break ;
		}
	}
	if (options[i].flag == 0) {
		printf("%s'%c'\n\n", MSG_INVALID_OPT, flag);
		handle_flag_h(NULL, NULL);
	}
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
		flag = argv[i];
		if (*flag == '-')
		{
			flag++;
			while (*flag != '\0')
			{
				if (*(flag + 1) != '\0')
					argument = (flag + 1);
				else if (i < argc)
					argument = argv[++i];
				else
					argument = NULL;
				__check_flag(&options, *flag, argument);
				flag++;
			}
		}
	}
	options.destination = argv[argc - 1];
	return (options);
}
