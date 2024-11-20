/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:30:34 by smishos           #+#    #+#             */
/*   Updated: 2024/04/27 15:40:34 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	convert_integer(long num, char *str, int i)
{
	while (i-- > 0)
	{
		str[i] = (num % 10) + '0';
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		negative;
	int		digits;
	char	*str;
	int		i;
	long	num;

	num = (long)n;
	negative = 0;
	if (num < 0)
	{
		negative = 1;
		num = -num;
	}
	digits = count_digits(n);
	i = digits + negative;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	convert_integer(num, str, i);
	if (negative)
		str[0] = '-';
	return (str);
}
