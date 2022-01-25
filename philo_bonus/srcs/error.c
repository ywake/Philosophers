/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 02:37:05 by ywake             #+#    #+#             */
/*   Updated: 2022/01/25 12:48:56 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include "my_semaphore.h"

void	my_exit(int status)
{
	sem_unlink(FORKS_SEM);
	sem_unlink(FINS_SEM);
	sem_unlink(LIVES_SEM);
	sem_unlink(PRINT_SEM);
	if (errno == EAGAIN || errno == ENOMEM || errno == EINVAL || errno == EINTR)
		kill(0, SIGKILL);
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
