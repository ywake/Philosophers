/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:42:07 by ywake             #+#    #+#             */
/*   Updated: 2022/01/10 12:55:39 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include "table.h"

typedef struct s_philo
{
	int				number;
	t_table			*table;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	size_t			last_eat;
	bool			is_died;

}	t_philo;

t_philo	*init_philosopher(t_table *table, int philo_number);
t_philo	*del_philosopher(t_philo *philo);
t_philo	**init_philosophers(t_table *table);
t_philo	**del_philosophers(t_philo **philos);

void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
bool	philo_dead(t_philo	*philo);

void	take_forks(t_philo *philo);
void	return_forks(t_philo *philo);

#endif
