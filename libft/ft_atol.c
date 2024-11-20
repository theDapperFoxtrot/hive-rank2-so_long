/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:47:04 by thedapperfo       #+#    #+#             */
/*   Updated: 2024/11/04 19:16:47 by smishos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atol(const char *str)
{
	int			i;
	long long	sign;
	long long	ret;
	long long	check;

	i = 0;
	sign = 1;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = sign * -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		check = ret;
		ret = (ret * 10) + (str[i++] - 48);
		if (check > ret && sign == 1)
			return (-1);
		if (check > ret && sign == -1)
			return (0);
	}
	return (ret * sign);
}
