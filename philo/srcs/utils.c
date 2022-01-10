/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:26:51 by ywake             #+#    #+#             */
/*   Updated: 2022/01/11 02:15:43 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <sys/time.h>
#include <stdbool.h>
#include <unistd.h>
#include "types.h"

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

t_timestamp	get_millitime(void)
{
	struct timeval	tv;
	t_timestamp		time_milli;

	gettimeofday(&tv, NULL);
	time_milli = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_milli);
}

t_timestamp	get_utime(void)
{
	struct timeval	tv;
	size_t			utime;

	gettimeofday(&tv, NULL);
	utime = tv.tv_sec * 1000 * 1000 + tv.tv_usec;
	return (utime);
}

#define ALLOW_ERROR_USEC 1000

/**
 * Reference from tkomatsu
 */
void	my_usleep(t_timestamp sleep_usec)
{
	t_timestamp	endtime;
	t_timestamp	lefttime;

	endtime = get_utime() + sleep_usec;
	lefttime = sleep_usec;
	while (lefttime > 0)
	{
		usleep(lefttime / 2);
		lefttime = endtime - get_utime();
	}
}
