/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:47:13 by ywake             #+#    #+#             */
/*   Updated: 2022/01/21 02:50:03 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H
# include <stdbool.h>
# include <pthread.h>
# include "settings.h"
# include "philosopher.h"
# include "fork.h"

enum e_table_mutex
{
	TABLE_IS_FINISH,
	TABLE_PRINTF,
	TABLE_SETTINGS,
	TABLE_PHILOSOPHERS,
	TABLE_TMP_PHILOS_NUM,
	TABLE_MUTEX_LEN,
};

typedef struct s_table
{
	int				tmp_philos_number;
	int				length;
	t_settings		*settings;
	t_philo			**philos;
	t_fork			**forks;
	pthread_t		observer;
	bool			finish;
	pthread_mutex_t	mutexes[TABLE_MUTEX_LEN];

}	t_table;

t_table	*init_table(int argc, char *argv[]);
t_table	*del_table(t_table *table);

void	print(t_table *table, const char *fmt, t_timestamp time, int number);

int		get_time_to_eat(t_table *table);
int		get_time_to_sleep(t_table *table);
void	set_finish(t_table *table);
bool	is_finish(t_table *table);

#endif
