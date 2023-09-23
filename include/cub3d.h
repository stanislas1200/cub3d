#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <time.h>

# define BOLD "\x1b[1m"
# define RESET "\x1b[0m"
# define RED "\x1b[0;31m"
# define GREEN "\x1b[0;32m"
# define MAGENTA "\x1b[0;35m"
# define YELLOW "\x1b[0;33m"

typedef struct s_node
{
	int				x;
	int				y;
	struct s_node	*next;
}	t_node;

typedef struct s_player
{
	int		x;
	int		y;
	int		floor;
	char	dir;
}	t_player;

typedef struct s_data
{
	int			i;
	int			j;
	int			height;
	int			player_nb;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor[3];
	int			ceiling[3];
	char		**map;
	t_node		*stack;
	t_player	player;
}	t_data;

void	set_map_from_file(char *path, t_data *data);
int		ft_strlen(char *str);
void	ft_error(char *str);
void	pg(int x, int y, int f, t_data *data);
void	push(t_node	**top, int x, int y);
void	pop(t_node	**top);
void	cleanup_stack(t_data *data);
void	error(t_data *data, char *error);
void	make_map(char *str, t_data *data);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_map(t_data *data, int height);
int		ft_atoi(const char *str);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	print_map(t_data *data);
void	play(t_data *data);

#endif