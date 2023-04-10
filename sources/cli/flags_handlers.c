/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:26:22 by user42            #+#    #+#             */
/*   Updated: 2023/04/10 11:13:33 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	handle_flag_h(t_cli *cli, char *argument)
{
	(void)(cli && argument);
	printf("%s", PING_HELP);
	exit(EXIT_SUCCESS);
}

void	handle_flag_v(t_cli *cli, char *argument)
{
	(void)argument;
	cli->verbose = true;
}

void	handle_flag_c(t_cli *cli, char *argument)
{
	long	value;
	char	msg[256] = {0};

	if (ft_is_integer(argument) == false) {
		sprintf(msg, "%s '%s'", MSG_INVALID_ARG, argument);
		fatal(EXIT_FAILURE, msg);
	}
	value = ft_atol(argument);
	if (!(value >= 1 && value <= __LONG_MAX__)) {
		sprintf(msg, "%s '%s': out of range: %d <= value <= %ld", MSG_INVALID_ARG, argument, 1, __LONG_MAX__);
		fatal(EXIT_FAILURE, msg);
	}
	cli->count = value;
}

void	handle_flag_i(t_cli *cli, char *argument)
{
	float	value;
	char	msg[256] = {0};

	if (ft_is_float(argument) == false) {
		sprintf(msg, "%s '%s'", MSG_INVALID_ARG, argument);
		fatal(EXIT_FAILURE, msg);
	}
	value = ft_atof(argument);
	if (value < MIN_INTERVAL)
		fatal(EXIT_FAILURE, MSG_FLOOD);
	cli->interval = value * 1000000;
}

void	handle_flag_D(t_cli *cli, char *argument)
{
	(void)argument;
	cli->timestamps = true;
}

void	handle_flag_q(t_cli *cli, char *argument)
{
	(void)argument;
	cli->quiet = true;
}

void	handle_flag_s(t_cli *cli, char *argument)
{
	int		value;
	char	msg[256] = {0};

	if (ft_is_integer(argument) == false) {
		sprintf(msg, "%s '%s'", MSG_INVALID_ARG, argument);
		fatal(EXIT_FAILURE, msg);
	}
	value = ft_atoi(argument);
	if (!(value >= 0 && value <= __INT32_MAX__)) {
		sprintf(msg, "%s '%s': out of range: %d <= value <= %d", MSG_INVALID_ARG, argument, 0, __INT32_MAX__);
		fatal(EXIT_FAILURE, msg);
	}
	cli->size = value;
}

void	handle_flag_t(t_cli *cli, char *argument)
{
	int		value;
	char	msg[256] = {0};

	if (ft_is_integer(argument) == false) {
		sprintf(msg, "%s '%s'", MSG_INVALID_ARG, argument);
		fatal(EXIT_FAILURE, msg);
	}
	value = ft_atoi(argument);
	if (!(value >= 0 && value <= __UINT8_MAX__)) {
		sprintf(msg, "%s '%s': out of range: %d <= value <= %d", MSG_INVALID_ARG, argument, 0, __UINT8_MAX__);
		fatal(EXIT_FAILURE, msg);
	}
	cli->ttl = value;
}

void	handle_flag_w(t_cli *cli, char *argument)
{
	int		value;
	char	msg[256] = {0};

	if (ft_is_integer(argument) == false) {
		sprintf(msg, "%s '%s'", MSG_INVALID_ARG, argument);
		fatal(EXIT_FAILURE, msg);
	}
	value = ft_atoi(argument);
	if (!(value >= 0 && value <= __INT32_MAX__)) {
		sprintf(msg, "%s '%s': out of range: %d <= value <= %d", MSG_INVALID_ARG, argument, 0, __INT32_MAX__);
		fatal(EXIT_FAILURE, msg);
	}
	cli->wait = value;
}

void	handle_flag_W(t_cli *cli, char *argument)
{
	int		value;
	char	msg[256] = {0};

	if (ft_is_integer(argument) == false) {
		dprintf(STDERR_FILENO, "%s: %s\n", MSG_OPT_GARBAGE, argument);
		dprintf(STDERR_FILENO, "%s\n", MSG_WARN_FATAL);
	}
	value = ft_atoi(argument);
	if (value > 2147483) {
		sprintf(msg, "%s: %s", MSG_BAD_LINGER_TIME, argument);
		fatal(EXIT_FAILURE, msg);
	}
	cli->timeout.tv_sec = value == 0 ? 1 : value;
}

void	handle_flag_4(t_cli *cli, char *argument)
{
	(void)argument;
	cli->family = PF_INET;
}

void	handle_flag_6(t_cli *cli, char *argument)
{
	(void)argument;
	cli->family = PF_INET6;
}

void	handle_flag_b(t_cli *cli, char *argument)
{
	(void)argument;
	cli->broadcast = true;
}

void	handle_flag_n(t_cli *cli, char *argument)
{
	(void)argument;
	cli->no_dns = true;
}
