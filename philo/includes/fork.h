/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:55:11 by ywake             #+#    #+#             */
/*   Updated: 2022/01/24 12:17:24 by ywake            ###   ########.fr       */
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
t_fork	**init_forks(size_t num);
t_fork	**del_forks(t_fork **forks);

bool	try_take_a_fork(t_fork *fork);
void	drop_a_fork(t_fork *fork);

#endif
