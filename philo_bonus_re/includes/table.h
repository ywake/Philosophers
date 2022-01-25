/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:13 by ywake             #+#    #+#             */
/*   Updated: 2022/01/25 17:34:24 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include <semaphore.h>

# include "settings.h"
# include "utils.h"

typedef struct s_table
{
	int			length;
	sem_t		*forks;
	sem_t		*num_of_finish_philos;
	sem_t		*everyone_is_alive;
	sem_t		*printf;

}	t_table;

t_table	*init_table(t_settings *settings);
t_table	*del_table(t_table *table);

void	print(t_table *table, const char *fmt, t_timestamp time, int number);

#endif
