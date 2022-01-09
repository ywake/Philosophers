/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:26:51 by ywake             #+#    #+#             */
/*   Updated: 2022/01/09 16:21:35 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <sys/time.h>
#include <stdbool.h>

int	ft_atoi(const char *str)
{
	int	sign;
	int	value;

	sign = 1;
	value = 0;
	while (('\t' <= *str && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		sign = 44 - *str++;
	while (*str && '0' <= *str && *str <= '9')
		value = value * 10 + (*str++ - '0');
	return (sign * value);
}

size_t	get_millitime(void)
{
	struct timeval	tv;
	size_t			time_milli;
	int				rtn;

	rtn = gettimeofday(&tv, NULL);
	time_milli = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_milli);
}
