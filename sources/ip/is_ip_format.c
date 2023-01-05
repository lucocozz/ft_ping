/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ip_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:44:54 by lucocozz          #+#    #+#             */
/*   Updated: 2023/01/05 22:46:54 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

bool	is_ip_format(int family, char *ip)
{
	struct in_addr	address;

  if (inet_pton(family, ip, &address) == 1)
    return (true);
  return (false);
}
