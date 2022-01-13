/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 02:37:05 by ywake             #+#    #+#             */
/*   Updated: 2022/01/13 17:59:27 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <stdlib.h>
#include "my_semaphore.h"

#include<stdio.h>
void	my_exit(int status)
{
	sem_unlink(FORKS_SEM);
	sem_unlink(FINS_SEM);
	sem_unlink(LIVES_SEM);
	sem_unlink(PRINT_SEM);
	exit(status);
}

int	catch_err(int status)
{
	if (status == -1)
		my_exit(1);
	return (status);
}

void	*catch_null(void *ptr)
{
	if (ptr == NULL)
		my_exit(1);
	return (ptr);
}
