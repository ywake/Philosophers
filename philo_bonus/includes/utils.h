/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:45:29 by ywake             #+#    #+#             */
/*   Updated: 2022/01/16 10:47:39 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include "types.h"

int			ft_atoi(const char *str, bool *error);
t_timestamp	get_timestamp(void);
void		my_usleep(t_timestamp usec);
void		kill_all_child(pid_t *pids, int length);

void		my_exit(int status);
int			catch_err(int status);
void		*catch_null(void *ptr);

#endif
