/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:47:13 by ywake             #+#    #+#             */
/*   Updated: 2022/01/23 11:31:01 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H
# include <stdbool.h>
# include <pthread.h>
# include "settings.h"
# include "fork.h"

typedef struct s_table
{
	int				length;
	t_fork			**forks;
	bool			finish;
	pthread_mutex_t	mutex;

}	t_table;

t_table	*init_table(t_settings *settings);
t_table	*del_table(t_table *table);

bool	is_finish(t_table **table);

#endif
