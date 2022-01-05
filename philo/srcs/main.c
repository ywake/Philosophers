/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:17:09 by ywake             #+#    #+#             */
/*   Updated: 2022/01/05 22:49:30 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "settings.h"

int	main(int argc, char *argv[])
{
	t_settings	settings;

	if (init_settings(&settings, argc, argv) == false)
		return (1);
}
