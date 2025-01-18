/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:55:03 by lle-duc           #+#    #+#             */
/*   Updated: 2025/01/16 11:37:37 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	here_doc_loop(char *limiter, int *pipefd)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			close(pipefd[1]);
			close(STDIN_FILENO);
			get_next_line(STDIN_FILENO);
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
			exit(0);
		}
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
}

void	here_doc_handle(char *limiter, int fd)
{
	char	*line;
	int		pipefd[2];
	int		pid;

	if (pipe(pipefd) == -1)
		print_errors_exit("ERROR : Pipe was not created!\n", EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		print_errors_exit("ERROR : Fork Failed!\n", EXIT_FAILURE);
	else if (pid == 0)
	{
		close(fd);
		close(pipefd[0]);
		here_doc_loop(limiter, pipefd);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], 0) == -1)
			print_errors_exit("ERROR : dup2 failed!\n", EXIT_FAILURE);
		close(pipefd[0]);
	}
}

void	prepare_exec_data(char *av, char **env)
{
	char	*buffer;
	char	*tmp;
	char	**split;
	char	*path;

	av = ft_strjoin(av, " ");
	if (!av)
		print_errors_exit("Memory allocation failed for av", EXIT_FAILURE);
	split = ft_split(av, ' ');
	if (!split)
		print_errors_exit("Memory allocation failed for split", EXIT_FAILURE);
	path = find_path(split[0], env);
	if (!path)
	{
		free(av);
		ft_freetab(split);
		print_errors_exit("Command does not exist / not found!", 127);
	}
	ft_freetab(split);
	execute(path, av, env);
}

void	pipex(int ac, char **av, char **env, int *exit_status)
{
	int		in_out_files[2];
	char	*str;
	int		i;
	int		here_doc;

	here_doc = 0;
	if (ft_strcmp(av[1], "here_doc") == 0)
		here_doc = 1;
	i = 2 + here_doc;
	in_out_files[0] = 0;
	in_out_files[1] = 0;
	check_files(av, in_out_files, ac, here_doc);
	if (in_out_files[0] == -1)
		i++;
	while (i < ac - 1)
	{
		if (i == ac - 2)
			create_pipe(av[i], env, exit_status, in_out_files[1]);
		else
			create_pipe(av[i], env, exit_status, -1);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	int	exit_status;

	exit_status = 0;
	if (ac >= 4)
	{
		pipex(ac, av, env, &exit_status);
	}
	else
		perror("Invalid argument count!");
	return (exit_status);
}
