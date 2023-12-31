/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:19:24 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/10 17:19:24 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <time.h>
# include <math.h>
# include <mlx.h>
# include <limits.h>
# include <pthread.h>
# include <sys/wait.h>

# define BOLD "\x1b[1m"
# define RESET "\x1b[0m"
# define RED "\x1b[0;31m"
# define GREEN "\x1b[0;32m"
# define MAGENTA "\x1b[0;35m"
# define YELLOW "\x1b[0;33m"

# define SQUARE 64
# define PLAYER 30
# define PI 3.1415926535
# define RD 0.0174533
# define PI2 6.283185307
# define PI3 9.4247779605
# define HEIGHT 512
# define WIDTH 1024
# define FOV 45.0
# define NO 0
# define SO 1
# define WE 2
# define EA 3

# define E_M "Invalid map"
# define P "Only one player is allowed\n"
# define C "Invalid character in map\n"
# define F "Invalid floor color\n"

// keys

//linux
// # define Z 122 
// # define Q 113
// # define D 100
// # define S 115
// # define ESC 65307
// # define A_E 65363
// # define A_W 65361

// MacOS
# define Z 13
# define Q 0
# define D 2
# define S 1
# define ESC 53
# define A_E 124
# define A_W 123

typedef struct s_img {
	void	*image;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct sprites {
	t_img	*wall[4];
}				t_sprites;

typedef struct drawing {
	double	line_h;
	double	line_o;
	double	ty_offset;
	double	tex_x;
	double	step;
	double	tex;
	double	realdist;

}	t_draw;
typedef struct ray
{
	double	rx;
	double	ry;
	double	ra;
	double	xo;
	double	yo;
	int		my;
	int		mx;
	int		hit;
	double	dist;
	int		side;
}	t_ray;

typedef struct s_node
{
	int				x;
	int				y;
	struct s_node	*next;
}	t_node;

typedef struct s_player
{
	double	px;
	double	py;
	int		floor;
	char	dir;
	double	pdx;
	double	pdy;
	double	pa;
	int		fov;
	float	speed;
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
	char		*all_line;
	t_node		*stack;
	t_player	player;
}	t_data;

typedef struct game
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_img		img;
	t_player	player;
	t_data		*data;
	t_sprites	sprites;
	float		old_x;
	int			keys[6];
	int			color;
}	t_game;

void	set_map_from_file(char *path, t_data *data);
int		ft_strlen(char *str);
void	ft_error(char *str);
void	pg(int x, int y, int f, t_data *data);
void	push(t_node	**top, int x, int y);
void	pop(t_node	**top);
void	cleanup_stack(t_data *data);
void	e(t_data *data, char *str, char *error);
void	make_map(char *str, t_data *data);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_map(t_data *data, int height);
int		ft_atoi(const char *str);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_all(t_data *data);
void	get_wall_texture_path(char **dest, char *str, char *str2, t_data *d);

//raycasting
void	draw_rays(t_game *game);
void	ray_cast(t_game *game, double angle, int s_width);

//rays
void	check_for_hit(t_game *game, t_ray *ray);
void	setup_horizontal_ray(t_ray *ray, t_game *game);
void	setup_vertical_ray(t_ray *ray, t_game *game);
void	init_ray(t_ray *ray, t_game *game, double angle, char type);

//render
void	drawstripes(t_game *game, int x1, int y1, int y2);
int		update_frame(t_game *game);

//movement
void	movement(t_game *game);
void	can_move(t_game *game, double fx, double fy);

//utils 2
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
double	distance(double x1, double y1, double x2, double y2);
double	deg_to_rad(double a);
double	fix_ang(double a);
void	put_img(t_game *data, t_img **i, char *path);
int		get_color(t_img *img, int x, int y);

//end
void	destroy_sprites(t_game *game);
int		end_game(t_game *game);

//init
int		init_mlx(t_game *game);
void	init_player(t_data *data, t_game *game);
int		init_sprites(t_game *game);
void	init_data(t_data *data);

#endif