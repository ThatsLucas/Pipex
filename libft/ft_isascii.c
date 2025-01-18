/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:39:38 by lle-duc           #+#    #+#             */
/*   Updated: 2024/11/23 23:01:15 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks if the character is an ASCII character.
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
