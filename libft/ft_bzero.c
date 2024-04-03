/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:17:25 by abausa-v          #+#    #+#             */
/*   Updated: 2024/04/03 16:21:00 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *dest, size_t count)
{
	unsigned char	*destiny;
	size_t			i;

	destiny = dest;
	i = 0;
	while (i < count)
	{
		destiny[i] = 0;
		i++;
	}
	return (destiny);
}
