/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_semaphore.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:44:13 by ywake             #+#    #+#             */
/*   Updated: 2022/01/25 11:44:13 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SEMAPHORE_H
# define MY_SEMAPHORE_H

# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define FORKS_SEM ("/forks")
# define FINS_SEM ("/num_of_finish_philos")
# define LIVES_SEM ("/everyone_is_alive")
# define PRINT_SEM ("/printf")

#endif
