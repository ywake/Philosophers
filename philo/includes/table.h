/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:13 by ywake             #+#    #+#             */
/*   Updated: 2022/01/10 14:32:00 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include "settings.h"
# include "fork.h"

enum e_fork_dir
{
	RIGHT,
	LEFT,
};

typedef struct s_table
{
	t_settings		*settings;
	t_fork			**forks;
	int				length;
	pthread_mutex_t	mutex;
	bool			is_someone_died;

}	t_table;

t_table	*init_table(t_settings *settings);
t_table	*del_table(t_table *table);

void	someone_died(t_table *table);
bool	is_someone_died(t_table *table);

#endif
