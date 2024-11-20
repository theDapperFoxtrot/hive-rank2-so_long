/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:28:03 by smishos           #+#    #+#             */
/*   Updated: 2024/04/27 15:42:50 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	character;

	ptr = (unsigned char *) s;
	character = (unsigned char) c;
	while (n--)
	{
		if (*ptr == character)
			return (ptr);
		ptr++;
	}
	return (0);
}
