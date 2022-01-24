/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:37:11 by ywake             #+#    #+#             */
/*   Updated: 2022/01/20 15:44:39 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <stddef.h>
#include <stdbool.h>

int	ft_atoi(const char *str, bool *error)
{
	int	sign;
	int	value;

	if (error != NULL)
		*error = (str == NULL);
	if (str == NULL)
		return (-1);
	sign = 1;
	value = 0;
	while (('\t' <= *str && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		sign = 44 - *str++;
	while (*str && '0' <= *str && *str <= '9')
	{
		value = value * 10 + (*str++ - '0');
		if (value < 0 && error != NULL)
			*error = true;
	}
	return (sign * value);
}
