/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:31:13 by ywake             #+#    #+#             */
/*   Updated: 2022/01/06 23:07:35 by ywake            ###   ########.fr       */
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

}	t_table;

t_table	*init_table(t_settings *settings, t_philosopher **philos);

#endif
