/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:13 by ywake             #+#    #+#             */
/*   Updated: 2022/01/06 23:48:34 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include "philosopher.h"

/**
 * philos: Philosophers sitting in their seats.
 * forks: If true, the fork exists, but if false, it doesn't.
 */
typedef struct s_table
{
	t_philosopher	**philos;	
	bool			*forks;
	int				length;

}	t_table;

t_table	*init_table(t_settings *settings, t_philosopher **philos);
void	take_a_fork(t_table *table, int philo_num, enum e_fork_dir direction);
void	return_a_fork(t_table *table, int philo_num, enum e_fork_dir direction);
#endif
