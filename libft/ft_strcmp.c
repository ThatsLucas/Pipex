/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:34:43 by lle-duc           #+#    #+#             */
/*   Updated: 2025/01/16 12:34:44 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compare two strings
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (!s1[i] && s2[i])
		return (-1);
	if (s1[i] && !s2[i])
		return (1);
	return (0);
}
