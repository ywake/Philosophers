/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:20:43 by ywake             #+#    #+#             */
/*   Updated: 2022/01/20 18:23:06 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <stddef.h>

// Returns -1 if src is NULL, 0 otherwise.
int	set(void **dest, void *src)
{
	*dest = src;
	if (src == NULL)
		return (-1);
	return (0);
}
