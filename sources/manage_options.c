/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:30:35 by user42            #+#    #+#             */
/*   Updated: 2022/12/07 01:36:49 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	__check_flag(char flag, char *parameter)
{
	uint					i = 0;
	static const t_option	options[] = {
		{.flag = 'h', .handler = &handle_flag_h, .parameter = false},
		{0}
	};
	
	for (i = 0; options[i].flag != 0; ++i) {
		if (flag == options[i].flag) {
			options[i].handler(options[i].parameter == false ? NULL : parameter);
			break ;
		}
	}
	if (options[i].flag == 0) {
		printf("%s'%c'\n", MSG_INVALID_OPT, flag);
		handle_flag_h(NULL);
	}
	
}

void	manage_options(int argc, char **argv)
{
	char	*flag;
	char	*parameter;

	for (int i = 1; i < argc; ++i)
	{
		flag = argv[i];
		if (*flag == '-') {
			flag++;
			if (i < argc - 1)
				parameter = argv[i + 1];
			else
				parameter = NULL;
			__check_flag(*flag, parameter);
		}
	}
}
