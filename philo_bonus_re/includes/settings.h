/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:21:07 by ywake             #+#    #+#             */
/*   Updated: 2022/01/16 11:17:47 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include <stdbool.h>

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
t_settings	*init_settings(int argc, char *argv[]);
t_settings	*del_settings(t_settings *settings);

#endif
