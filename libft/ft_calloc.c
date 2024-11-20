/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:45:02 by smishos           #+#    #+#             */
/*   Updated: 2024/10/10 16:54:54 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//allocate memory for the requested size and initialize each byte to zero
//return a pointer to the start of the allocated memory block
void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (!count && !size)
		return (ft_calloc(1, 1));
	total_size = count * size;
	if ((count != 0 && total_size / count != size) || total_size > 2147483648)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	if (ptr)
		ft_memset(ptr, 0, total_size);
	return (ptr);
}
