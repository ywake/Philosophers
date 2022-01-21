/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:05:36 by ywake             #+#    #+#             */
/*   Updated: 2022/01/20 18:19:26 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include "settings.h"
# include "utils.h"

enum	e_philo_mutex
{
	LAST_EAT,
	LEFT_NUM_OF_EAT,
	TABLE,
	PHILO_MUTEX_LEN,
};

typedef struct s_philo
{
	int				number;
	pthread_t		thread;
	t_timestamp		last_eat;
	int				left_num_of_eat;
	pthread_mutex_t	mutexes[PHILO_MUTEX_LEN];

}	t_philo;

t_philo		*init_philosopher(t_settings *settings, int philo_number);
t_philo		*del_philosopher(t_philo *philo);
t_philo		**init_philosophers(t_settings *settings);
t_philo		**del_philosophers(t_philo **philos);

t_timestamp	get_last_eat(t_philo **philo);
void		set_last_eat(t_philo **philo, t_timestamp last_eat);
int			get_left_num_of_eat(t_philo **philo);
void		decrement_left_num_of_eat(t_philo **philo);

#endif
