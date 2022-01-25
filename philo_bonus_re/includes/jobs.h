/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:29:23 by ywake             #+#    #+#             */
/*   Updated: 2022/01/25 17:12:47 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_H
# define JOBS_H

# include <sys/wait.h>
# include "table.h"
# include "philosopher.h"

void	observe_job(t_table *table);
void	philo_job(t_philo *philo);
void	kill_all_child(pid_t *pids, size_t length);

#endif
