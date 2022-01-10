/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:13 by ywake             #+#    #+#             */
/*   Updated: 2022/01/10 12:55:13 by ywake            ###   ########.fr       */
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
	t_settings	*settings;
	t_fork		**forks;
	int			length;

}	t_table;

t_table	*init_table(t_settings *settings);
t_table	*del_table(t_table *table);

#endif
