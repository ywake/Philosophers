/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:42:07 by ywake             #+#    #+#             */
/*   Updated: 2022/01/06 18:50:32 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "settings.h"

typedef struct s_philosopher
{
	int	number;

}	t_philosopher;

t_philosopher	**init_philosopher(t_settings *settings);
void			eat(t_philosopher *philo);
void			sleep(t_philosopher *philo);
void			think(t_philosopher *philo);

#endif
