/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:13 by ywake             #+#    #+#             */
/*   Updated: 2022/01/13 17:28:53 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include "my_semaphore.h"
# include "settings.h"
# include "types.h"

typedef struct s_table
{
	t_settings	*settings;
	int			length;
	sem_t		*forks;
	sem_t		*num_of_finish_philos;
	sem_t		*num_of_living_philos;
	sem_t		*printf;

}	t_table;

t_table	*init_table(t_settings *settings);
t_table	*del_table(t_table *table);

void	print(t_table *table, const char *fmt, t_timestamp time, int number);

#endif
