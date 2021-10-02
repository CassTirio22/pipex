/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:29:05 by ctirions          #+#    #+#             */
/*   Updated: 2021/10/02 16:44:00 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_my_lst(char **lst)
{
	int	size;

	size = -1;
	while (lst[++size])
		free(lst[size]);
	free(lst[++size]);
	free(lst);
}

void	ft_error(int flag)
{
	if (!flag)
		write(1, "Wrong number of arguments!\n", 27);
	else if (flag == 1)
		write(1, "Error !\n", 8);
	exit(1);
}

char	*pathfinder(char *cmd, char **env)
{
	char	**paths;
	char	*part_path;
	char	*path;
	int		i;

	i = -1;
	while (!ft_strnstr(env[++i], "PATH", 4))
		;
	paths = ft_split(env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free (part_path);
		if (!access(path, F_OK))
		{
			free_my_lst(paths);
			return (path);
		}
	}
	free_my_lst(paths);
	return (0);
}

pid_t	init_pid(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error(1);
	return (pid);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		ft_error(0);
	if (pipe(fd) == -1)
		ft_error(1);
	pid = init_pid();
	if (!pid)
		begin_pipe(argv, env, fd);
	else
		end_pipe(argv, env, fd);
	waitpid(pid, 0, 0);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
