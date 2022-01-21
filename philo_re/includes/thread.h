/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:44:27 by ywake             #+#    #+#             */
/*   Updated: 2022/01/21 02:18:50 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include "table.h"

int		run_threads(t_table **table);
void	*routine(void *arg);
void	*observe(void *arg);

void	philo_eat(t_table **table, int philo_number);
void	philo_sleep(t_table **table, int philo_number);
void	philo_think(t_table **table, int philo_number);

void	take_forks(t_table **table, int philo_number);
void	return_forks(t_table **table, int philo_number);

#endif
