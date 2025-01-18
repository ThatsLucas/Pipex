/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:22:08 by lle-duc           #+#    #+#             */
/*   Updated: 2025/01/16 11:34:06 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_errors_exit(char *str, int exit_status)
{
	perror(str);
	exit(exit_status);
}

char	*try_access_program(char **paths, char *program)
{
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		tmp = full_path;
		full_path = ft_strjoin(full_path, program);
		free(tmp);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

void	create_pipe(char *av, char **env, int *exit_status, int last)
{
	int	pipefd[2];
	int	pid;

	if (pipe(pipefd) == -1)
		print_errors_exit("ERROR : Pipe was not created!\n", EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		print_errors_exit("ERROR : Fork Failed!\n", EXIT_FAILURE);
	else if (pid == 0)
		manage_child_side(pipefd, last, av, env);
	else
		manage_parent_side(pipefd[0], pipefd[1], exit_status, pid);
}

void	execute(char *path, char *av, char **env)
{
	char	**split;

	av = ft_strjoin(av, " ");
	split = ft_split(av, ' ');
	free(av);
	if (!split)
		print_errors_exit("Memory allocation failed for split", EXIT_FAILURE);
	if (execve(path, split, env) == -1)
	{
		free(path);
		ft_freetab(split);
		perror("execve failed!");
	}
}
