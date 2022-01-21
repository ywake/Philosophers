/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:18:14 by ywake             #+#    #+#             */
/*   Updated: 2022/01/20 18:18:17 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <sys/time.h>
#include <unistd.h>

t_timestamp	get_timestamp(void)
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
