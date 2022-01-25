/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:43:55 by ywake             #+#    #+#             */
/*   Updated: 2022/01/25 15:58:09 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <sys/types.h>

typedef ssize_t	t_timestamp;

int			set(void **dest, void *src);

int			ft_atoi(const char *str, bool *error);
// void		*ft_calloc(size_t count, size_t size);

t_timestamp	get_timestamp(void);
void		my_usleep(t_timestamp sleep_usec);

void		my_exit(int status);
int			catch_err(int status);
void		*catch_null(void *ptr);

#endif
