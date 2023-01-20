/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:26:22 by user42            #+#    #+#             */
/*   Updated: 2023/01/20 00:21:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	handle_flag_h(t_options *data, char *argument)
{
	(void)(data && argument);
	printf("%s", PING_HELP);
	exit(EXIT_SUCCESS);
}

void	handle_flag_v(t_options *data, char *argument)
{
	(void)argument;
	data->verbose = true;
}

void	handle_flag_c(t_options *data, char *argument)
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
	data->count = value;
}

void	handle_flag_i(t_options *data, char *argument)
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
	data->interval = value * 1000000;
}

void	handle_flag_D(t_options *data, char *argument)
{
	(void)argument;
	data->timestamps = true;
}

void	handle_flag_q(t_options *data, char *argument)
{
	(void)argument;
	data->quiet = true;
}

void	handle_flag_s(t_options *data, char *argument)
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
	data->size = value;
}

void	handle_flag_t(t_options *data, char *argument)
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
	data->ttl = value;
}

void	handle_flag_w(t_options *data, char *argument)
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
	data->wait = value;
}

void	handle_flag_W(t_options *data, char *argument)
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
	data->timeout.tv_sec = value == 0 ? 1 : value;
}

void	handle_flag_4(t_options *data, char *argument)
{
	(void)argument;
	data->family = PF_INET;
}

void	handle_flag_6(t_options *data, char *argument)
{
	(void)argument;
	data->family = PF_INET6;
}

void	handle_flag_b(t_options *data, char *argument)
{
	(void)argument;
	data->broadcast = true;
}

void	handle_flag_n(t_options *data, char *argument)
{
	(void)argument;
	data->no_dns = true;
}
