/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:45:29 by ywake             #+#    #+#             */
/*   Updated: 2022/01/16 10:38:41 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include "types.h"

int			ft_atoi(const char *str, bool *error);
t_timestamp	get_timestamp(void);
void		my_usleep(t_timestamp usec);

#endif
