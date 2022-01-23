/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:05:36 by ywake             #+#    #+#             */
/*   Updated: 2022/01/23 11:52:44 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include "table.h"
# include "settings.h"
# include "utils.h"

typedef struct s_philo
{
	t_settings		*settings;
	t_table			*table;
	int				number;
	pthread_t		thread;
	t_timestamp		last_eat;
	int				left_num_of_eat;

}	t_philo;

t_philo		*init_philosopher(t_settings *s, t_table *t, int philo_number);
t_philo		*del_philosopher(t_philo *philo);
t_philo		**init_philosophers(t_settings *settings, t_table *table);
t_philo		**del_philosophers(t_philo **philos);

t_timestamp	take_right_fork(t_philo **philo);
t_timestamp	take_left_fork(t_philo **philo);
t_timestamp	philo_eat(t_philo **philo);
t_timestamp	philo_eat_done(t_philo **philo);
t_timestamp	philo_sleep(t_philo **philo);
t_timestamp	philo_think(t_philo **philo);

#endif
