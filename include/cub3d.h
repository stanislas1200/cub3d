#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define BOLD "\033[1m"
# define RESET "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"

typedef struct	s_player
{
	int	x;
	int	y;
	float	dir;
}	t_player;

typedef struct	s_data
{
	int		i;
	int		width;
	int		height;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor[3];
	int		ceiling[3];
	char	**map;
	t_player	player;
}	t_data;

void	set_map_from_file(char *path, t_data *data);
int	ft_strlen(char *str);

#endif