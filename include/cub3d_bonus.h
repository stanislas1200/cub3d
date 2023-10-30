/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:23:42 by sgodin            #+#    #+#             */
/*   Updated: 2023/10/10 18:23:42 by sgodin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
# define HEIGHT 1024
# define WIDTH 2048
# define FOV 90.0
# define NO 0
# define SO 1
# define WE 2
# define EA 3

# define GUN_H 360
# define GUN_W 300

# define MAP_W 200
# define MAP_C 5
# define MAP_CENTER 100
# define MAP_GROUND 0x002d75
# define MAP_PLAYER 0x0063ff
# define MAP_WALL 0x004abf
# define MAP_BG 0x001330
# define MAP_MOB 0xff3333
# define MAP_DOOR 0x00aeff

// keys

//linux
// # define Z 122
// # define Q 113
// # define D 100
// # define S 115
// # define ESC 65307
// # define A_E 65361
// # define A_W 65363

// MacOS
# define Z 13
# define Q 0
# define D 2
# define S 1
# define ESC 53
# define SPACE 49
# define F 3
# define A_E 123
# define A_W 124

typedef struct line
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
}	t_line;

typedef struct square
{
	double			x;
	double			y;
	int				size;
	unsigned int	color;
}	t_square;

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
	t_img	*wall_i[4];
	t_img	*wall_m[4];
	t_img	*gun[4];
	t_img	*egg[4];
	t_img	*egg_e[4];
	t_img	*chubb_s[4];
	t_img	*chubb_w[4];
	t_img	*chubb_a[4];
	t_img	*abutor_w[4];
	t_img	*abutor_s[15];
	t_img	*abutor_a[15];
	t_img	*heal0[2];
	t_img	*heal1[2];
	t_img	*heal2[2];
	t_img	*win;
	t_img	*loss;
	t_img	*red_b;
	t_img	*green_b;
}				t_sprites;

typedef struct wall_drawing {
	t_img	*i;
	double	line_h;
	double	line_o;
	double	ty_offset;
	double	tex_x;
	double	step;
	double	realdist;
}	t_draw;

typedef struct img_drawing {
	t_img	*img;
	int		startx;
	int		starty;
	int		width;
	int		height;
	double	stepx;
	double	stepy;
	int		endx;
	int		endy;
}	t_idraw;

typedef struct monster_drawing {
	double	line_h;
	double	line_o;
	double	ty_offset;
	double	tex_x;
	double	tex_y;
	double	stepy;
	double	stepx;
	double	dist;
	double	fog;
	int		startx;
	int		endx;
}	t_mdraw;

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
	int		hp;
	int		max_hp;
	int		trip;
	int		trip_cd;
	int		hurt;
	int		hurt_cd;
}	t_player;

typedef struct s_anode {
	float			g;
	float			f;
	int				x;
	int				y;
	struct s_anode	*previous;
}	t_anode;

typedef struct s_astar {
	t_anode	**open;
	t_anode	**closed;
	t_anode	**path;
	int		open_count;
	int		closed_count;
	int		path_count;
	t_anode	*start;
	t_anode	*end;
	t_anode	*current;
	t_anode	***nodes;
	int		size;
}	t_astar;

enum e_state {
	FOLLOW,
	IDLE,
	ATTACK,
	HIDE,
	MOVE,
	DEAD,
	DYING,
};

enum e_type {
	EGG,
	CHUBBS,
	ABUTOR,
};

typedef struct monster
{
	int				hp;
	int				max_hp;
	int				attack_type;
	double			x;
	double			y;
	int				speed;
	int				cd;
	int				type;
	int				frame;
	enum e_state	state;
	struct monster	*next;
}	t_mob;

typedef struct s_data
{
	int			i;
	int			j;
	int			height;
	int			biggest_w;
	int			player_nb;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor[3];
	int			ceiling[3];
	char		**map;
	char		*all_line;
	int			time;
	int			g_time;
	int			fired;
	float		fade_cd;
	t_node		*stack;
	t_player	player;
	t_astar		*a;
	t_mob		*mob_list;
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
	int			keys[7];
	pthread_t	t_id;
	t_img		map;
	int			color;
	t_img		*mob;
	t_mob		monster;
	t_img		*crosshair;
	t_img		monster_draw;
	double		depths[2048];
	int			status;
}	t_game;

void			set_map_from_file(char *path, t_data *data);
int				ft_strlen(char *str);
void			ft_error(char *str);
void			pg(int x, int y, int f, t_data *data);
void			push(t_node	**top, int x, int y);
void			pop(t_node **top);
void			cleanup_stack(t_data *data);
void			e(t_data *data, char *str, char *error);
void			make_map(char *str, t_data *data);
char			*ft_strjoin(char const *s1, char const *s2);
void			free_map(t_data *data, int height);
int				ft_atoi(const char *str);
size_t			ft_strlcpy(char *dest, char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			free_all(t_data *data);
void			get_wall_texture_path(char **dest, \
				char *str, char *str2, t_data *d);
void			play_sound(char *sound);
void			free_nodes(t_data *data, t_astar *a);
void			remove_arr(t_anode *arr[], t_anode *node, int size);
void			mob_move(t_game *game, t_mob *this);

//A*
void			init_astar(t_astar *a);
void			setup_astar(t_data *data, t_astar *a);
void			astar(t_data *data, t_astar *a, int start[], int end[]);
void			free_list(t_anode *arr[], int size);
t_anode			*new_node(int x, int y);
t_anode			*copy_node(t_anode *node);

//Monster
void			generate_monster(t_data *data, int type);
void			execute_mob(t_game *game, t_mob *this);

//raycasting
void			draw_rays(t_game *game);
void			ray_cast(t_game *game, double angle, int s_width);
int				in_map(t_game *game, int x, int y);
//rays
void			check_for_hit(t_game *game, t_ray *ray);
void			setup_horizontal_ray(t_ray *ray, t_game *game);
void			setup_vertical_ray(t_ray *ray, t_game *game);
void			init_ray(t_ray *ray, t_game *game, double angle, char type);

//render 1 && 2
void			drawstripes(t_game *game, int x1, int y1, int y2);
int				update_frame(t_game *game);
int				in_view(t_game *game);
void			setup_img(t_img *img, t_game *game, int pos[4], double size);
void			draw_img(t_game *game, t_idraw *i);

//movement
void			movement(t_game *game);
void			can_move(t_game *game, double fx, double fy, int side);

//utils 2
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
double			distance(double x1, double y1, double x2, double y2);
double			deg_to_rad(double a);
double			fix_ang(double a);
void			put_img(t_game *data, t_img **i, char *path);
unsigned int	get_color(t_img *img, int x, int y);

//end
void			destroy_sprites(t_game *game);
int				end_game(t_game *game);

//init
int				init_mlx(t_game *game);
void			init_player(t_data *data, t_game *game);
void			init_data(t_data *data);

//minimap 1 && 2
void			render_minimap(t_game *game);
int				in_minimap(double x1, double y1);
void			draw_entity(t_game *game, int x, int y, unsigned int color);
double			square_size(void);
void			draw_square(t_game *game, t_square square);
void			drawline(t_game *game, t_line l);

//raycasting/mob
void			draw_monster(t_game *game);
int				in_view(t_game *game);

//sprites
void			destroy_sprites(t_game *game);
void			destroy_sprites2(t_game *game);
void			set_sprites_null(t_game *game);
void			mob_put_img(t_game *game);
void			mob_put_img2(t_game *game);
void			mob_put_img3(t_game *game);
int				sprites_addr(t_game *game);
int				init_addr_array(t_img **arr, int size);
int				init_sprites(t_game *game);
void			hud_out_img(t_game *game);

#endif