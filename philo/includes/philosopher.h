/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:42:07 by ywake             #+#    #+#             */
/*   Updated: 2022/01/09 12:14:55 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include "table.h"

typedef struct s_philo
{
	int			number;
	pthread_t	*thread;
	t_table		*table;

}	t_philo;

t_philo	*init_philosopher(t_table *table, int philo_number);
t_philo	*del_philosopher(t_philo *philo);
t_philo	**init_philosophers(t_table *table);
t_philo	**del_philosophers(t_philo **philos);

void	philo_eat(t_table *table, int philo_number);
void	philo_sleep(t_table *table, int philo_number);
void	philo_think(t_table *table, int philo_number);

#endif
