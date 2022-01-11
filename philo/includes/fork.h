/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 01:37:00 by ywake             #+#    #+#             */
/*   Updated: 2022/01/11 02:49:38 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_fork
{
	bool			ready;
	pthread_mutex_t	mutex;

}	t_fork;

t_fork	*init_fork(void);
t_fork	*del_fork(t_fork *fork);
bool	_take(t_fork *fork);
void	_return(t_fork *fork);

#endif
