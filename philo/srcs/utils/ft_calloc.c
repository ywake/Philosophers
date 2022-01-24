/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:24:54 by ywake             #+#    #+#             */
/*   Updated: 2022/01/20 18:17:20 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <stdlib.h>
#include <string.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	memset(ptr, 0, count * size);
	return (ptr);
}
