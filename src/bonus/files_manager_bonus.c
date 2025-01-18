/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manager_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:55:17 by lle-duc           #+#    #+#             */
/*   Updated: 2025/01/16 11:37:18 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *program, char **env)
{
	char	*path;
	char	**paths;
	char	*full_path;
	int		i;

	path = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			break ;
		}
		i++;
	}
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	full_path = try_access_program(paths, program);
	ft_freetab(paths);
	return (full_path);
}

static void	check_files_validity(char **av, int ac, int here_doc)
{
	if (here_doc)
	{
		if (access(av[ac - 1], F_OK) != -1)
		{
			if (access(av[ac - 1], W_OK | R_OK) == -1)
				print_errors_exit("ERROR : Can't write or read to outfile!\n",
					EXIT_FAILURE);
		}
	}
	else
	{
		if (access(av[1], F_OK | R_OK) == -1)
		{
			perror("ERROR : Can't read to infile or infile doesn't exist!\n");
		}
		if (access(av[ac - 1], F_OK) != -1)
		{
			if (access(av[ac - 1], F_OK | W_OK) == -1)
			{
				print_errors_exit("ERROR : Can't write to outfile!\n",
					EXIT_FAILURE);
			}
			unlink(av[ac - 1]);
		}
	}
}

void	check_files(char **av, int *tab, int ac, int here_doc)
{
	check_files_validity(av, ac, here_doc);
	if (!here_doc)
	{
		tab[0] = open(av[1], O_RDONLY);
		tab[1] = open(av[ac - 1], O_WRONLY | O_CREAT, 00400 | 00200);
		if (tab[0] != -1)
		{
			if (dup2(tab[0], 0) == -1)
				print_errors_exit("ERROR : dup2 failed!\n", EXIT_FAILURE);
			close(tab[0]);
		}
		else
		{
			close(0);
			perror("ERROR : Can't open all files!\n");
		}
	}
	else
	{
		tab[1] = open(av[ac - 1], O_RDWR | O_APPEND | O_CREAT, 00400 | 00200);
		here_doc_handle(av[2], tab[1]);
	}
}
