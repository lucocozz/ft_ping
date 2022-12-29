/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_service.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:32:30 by lucocozz          #+#    #+#             */
/*   Updated: 2022/12/24 12:32:37 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

struct addrinfo	*resolve_service(const char *service, int family)
{
	struct addrinfo	hints = {0};
	struct addrinfo	*result = {0};
	char			msg[256] = {0};

	hints.ai_family = family;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = (family == PF_INET ? IPPROTO_ICMP : IPPROTO_ICMPV6);
	if (getaddrinfo(service, NULL, &hints, &result) < 0) {
		sprintf(msg, "%s: Name or service not known", service);
		fatal(EXIT_FAILURE, msg);
	}
	return (result);
}
