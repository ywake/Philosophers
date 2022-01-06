/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:42:07 by ywake             #+#    #+#             */
/*   Updated: 2022/01/06 23:37:10 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "settings.h"

enum e_fork_dir
{
	RIGHT,
	LEFT,
};

typedef struct s_philosopher
{
	int		number;
	bool	forks[2];

}	t_philosopher;

t_philosopher	**init_philosophers(t_settings *settings);
void			philo_eat(t_settings *settings, t_philosopher *philo);
void			philo_sleep(t_settings *settings, t_philosopher *philo);
void			philo_think(t_settings *settings, t_philosopher *philo);

#endif
