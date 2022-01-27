/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:38:14 by ywake             #+#    #+#             */
/*   Updated: 2022/01/28 01:13:59 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include <stdbool.h>

# define MAX_THREADS (32765)

typedef struct s_settings
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_times;
	int	target_num_of_eat;

}	t_settings;

bool		validity_check(int argc, char *argv[]);
void		init_settings(t_settings *settings, int argc, char *argv[]);

#endif
