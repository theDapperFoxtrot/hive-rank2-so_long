/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:02:28 by smishos           #+#    #+#             */
/*   Updated: 2024/04/27 15:41:16 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t length)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (length > 0)
	{
		*(ptr) = (unsigned char)c;
		ptr++;
		length--;
	}
	return (b);
}
