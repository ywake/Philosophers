/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:13 by ywake             #+#    #+#             */
/*   Updated: 2022/01/11 10:48:01 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include "settings.h"
# include "fork.h"
# include "types.h"

typedef struct s_table
{
	t_settings		*settings;
	t_fork			**forks;
	int				length;
	pthread_mutex_t	mutex;
	bool			is_finish;
	pthread_mutex_t	printf_mutex;

}	t_table;

t_table	*init_table(t_settings *settings);
t_table	*del_table(t_table *table);

void	set_finish(t_table *table);
bool	is_finish(t_table *table);

void	print(t_table *table, const char *fmt, t_timestamp time, int number);

#endif
