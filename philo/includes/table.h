/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:13 by ywake             #+#    #+#             */
/*   Updated: 2022/01/20 13:46:25 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include "settings.h"
# include "fork.h"
# include "types.h"

enum e_table_mutex
{
	IS_FINISH,
	PRINTF,
	SETTINGS,
	TABLE_MUTEX_LEN,
};

typedef struct s_table
{
	t_settings		*settings;
	t_fork			**forks;
	int				length;
	bool			is_finish;
	pthread_mutex_t	mutexes[TABLE_MUTEX_LEN];

}	t_table;

t_table	*init_table(t_settings *settings);
t_table	*del_table(t_table *table);

int		time_to_eat(t_table *table);
int		time_to_sleep(t_table *table);
void	set_finish(t_table *table);
bool	is_finish(t_table *table);

void	print(t_table *table, const char *fmt, t_timestamp time, int number);

#endif
