/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:50:41 by lle-duc           #+#    #+#             */
/*   Updated: 2024/12/05 16:50:48 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_valid_base(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (ft_strlen(str) < 2)
		return (0);
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[i] == str[j] || str[j] == '-' || str[j] == '+')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_putnbr_base(size_t nb, char *base, int *c_cnt)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (ft_is_valid_base(base))
	{
		if (nb >= base_len)
			ft_putnbr_base(nb / base_len, base, c_cnt);
		*c_cnt += 1;
		write(1, &base[nb % base_len], 1);
	}
}
