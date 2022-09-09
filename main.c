#include "so_long.h"

// //gets the right asset
void *put_the_img(char c)
{

	if (c == '1')
		return "./assets/brick.xpm";
	else if (c == 'E')
		return "./assets/exit.xpm";
	else if (c == '0' || c == 'P' || c == 'C')
		return "./assets/empty.xpm";
	return NULL;
}

// // gets the file content length
int parse_map(int *width, int *height)
{
	*width = 0;
	*height = 0;
	int fd = open("./maps/map.ber", O_RDONLY);
	char *line = get_next_line(fd);
	int len = 0;
	while (line)
	{
		len += ft_strlen(line);
		*height += 20;
		line = get_next_line(fd);
	}
	*width = len / (*height / 20) * 20;
	close(fd);
	return len;
}

bool map_value_validation(char value)
{
	if (value == '0' || value == '1' || value == 'P' || value == 'C' || value == 'E')
		return true;
	return false;
}

void create_player(struct window *game_window, int *h_score, int *h_lives)
{
	game_window->hero.asset = "./assets/player.xpm";
	game_window->hero.scores = h_score;
	game_window->hero.lives = h_lives;
	game_window->hero.size = 20;
	game_window->hero.object = (void *)malloc(sizeof(void *) * 10);
	game_window->hero.object = mlx_xpm_file_to_image(game_window->mlx, "./assets/player.xpm", &game_window->hero.size, &game_window->hero.size);
	mlx_put_image_to_window(game_window->mlx, game_window->mlx_window, game_window->hero.object, game_window->hero.x, game_window->hero.y);
}

int ft_strcmp(char *s1, char *s2)
{
	int c;

	c = 0;
	while ((s1[c] == s2[c]) && (s1[c] != '\0') && (s2[c] != '\0'))
	{
		c++;
	}
	return (s1[c] - s2[c]);
}

void get_map_value(struct window *game_window, char **map_value)
{

	int read_map;
	int row;
	int column;
	int i = 0;
	int player_index;
	read_map = open("./maps/map.ber", O_RDWR);

	row = game_window->hero.y / 20;
	column = game_window->hero.x / 20;

	while (--row)
	{
		get_next_line(read_map);
	}
	i = 0;
	while (i < 3)
	{
		read(read_map, map_value[i], column + 2);
		get_next_line(read_map);
		i++;
	}
	close(read_map);
}

void get_the_row(int row, int column, char *map_value)
{
	int read_map;
	read_map = open("./maps/map.ber", O_RDWR);
	while (--row)
	{
		get_next_line(read_map);
	}
	read(read_map, map_value, column + 2);
}

unsigned int ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int count;
	unsigned int index;

	count = 0;
	index = 0;
	while (src[count] != '\0')
		count++;
	if (size != 0)
	{
		while (src[index] != '\0' && index < (size - 1))
		{
			dest[index] = src[index];
			index++;
		}
		dest[index] = '\0';
	}
	return (count);
}

bool walk(struct window *game_window, char **map_value, char *dir)
{
	int column;
	int row;
	column = game_window->hero.x / 20;
	row = game_window->hero.y / 20;

	if (!ft_strcmp(dir, "left") && map_value[1][column + 1] != '1')
	{
		map_value[1][column] = '0';
		map_value[1][column + 1] = 'P';
		return true;
	}
	else if (!ft_strcmp(dir, "right") && map_value[1][column - 1] != '1')
	{
		map_value[1][column] = '0';
		map_value[1][column - 1] = 'P';
		return true;
	}
	else if (!ft_strcmp(dir, "up") && map_value[0][column] != '1')
	{
		map_value[1][column] = '0';
		map_value[0][column] = 'P';
		ft_strlcpy(map_value[2], map_value[1], ft_strlen(map_value[1]) + 1);
		ft_strlcpy(map_value[1], map_value[0], ft_strlen(map_value[1]) + 1);
		get_the_row(row - 1, column, map_value[0]);
		return true;
	}
	else if (!ft_strcmp(dir, "down") && map_value[2][column] != '1')
	{
		map_value[1][column] = '0';
		map_value[2][column] = 'P';
		ft_strlcpy(map_value[0], map_value[1], ft_strlen(map_value[1]) + 1);
		ft_strlcpy(map_value[1], map_value[2], ft_strlen(map_value[1]) + 1);
		get_the_row(row + 2, column, map_value[2]);
		return true;
	}
	return false;
}

// TODO:change the name, make function shorter. Recursion?
int close_the_window(int key_code, struct window *game_window)
{
	struct free_space background;
	char **map_value;
	int i = 0;
	int map_width = 48;
	map_value = (char **)malloc(3 * sizeof(char *));

	while (i < 3)
	{
		map_value[i] = (char *)malloc(sizeof(char) * map_width);
		i++;
	}
	get_map_value(game_window, map_value);
	if (key_code == 53)
	{
		free(game_window->assets);
		exit(0);
	}
	else if (key_code == 124 && walk(game_window, map_value, "left"))
	{
		background.object = mlx_xpm_file_to_image(game_window->mlx, "./assets/empty.xpm", &game_window->hero.size, &game_window->hero.size);
		mlx_put_image_to_window(game_window->mlx, game_window->mlx_window, background.object, game_window->hero.x, game_window->hero.y);
		game_window->hero.x += 20;
		mlx_put_image_to_window(game_window->mlx, game_window->mlx_window, game_window->hero.object, game_window->hero.x, game_window->hero.y);
	}
	else if (key_code == 123 && walk(game_window, map_value, "right"))
	{
		background.object = mlx_xpm_file_to_image(game_window->mlx, "./assets/empty.xpm", &game_window->hero.size, &game_window->hero.size);
		mlx_put_image_to_window(game_window->mlx, game_window->mlx_window, background.object, game_window->hero.x, game_window->hero.y);
		game_window->hero.x -= 20;
		mlx_put_image_to_window(game_window->mlx, game_window->mlx_window, game_window->hero.object, game_window->hero.x, game_window->hero.y);
	}
	else if (key_code == 126 && walk(game_window, map_value, "up"))
	{
		background.object = mlx_xpm_file_to_image(game_window->mlx, "./assets/empty.xpm", &game_window->hero.size, &game_window->hero.size);
		mlx_put_image_to_window(game_window->mlx, game_window->mlx_window, background.object, game_window->hero.x, game_window->hero.y);
		game_window->hero.y -= 20;
		mlx_put_image_to_window(game_window->mlx, game_window->mlx_window, game_window->hero.object, game_window->hero.x, game_window->hero.y);
	}
	else if (key_code == 125 && walk(game_window, map_value, "down"))
	{
		background.object = mlx_xpm_file_to_image(game_window->mlx, "./assets/empty.xpm", &game_window->hero.size, &game_window->hero.size);
		mlx_put_image_to_window(game_window->mlx, game_window->mlx_window, background.object, game_window->hero.x, game_window->hero.y);
		game_window->hero.y += 20;
		mlx_put_image_to_window(game_window->mlx, game_window->mlx_window, game_window->hero.object, game_window->hero.x, game_window->hero.y);
	}
	return (0);
}
// TODO: Find the best solution for map sizes
void prepare_the_map()
{
	int main_map;
	int game_map;
	char x;
	int i = 678;
	main_map = open("./maps/map.ber", O_RDONLY);
	game_map = open("./maps/game_map.ber", O_RDWR);
	read(main_map, &x, 1);
	while (i)
	{
		write(game_map, &x, 1);
		read(main_map, &x, 1);
		i--;
	}
}
// //TODO: separate code into functions
int main(void)
{
	struct window game_window;
	int map;
	char map_value;
	int i;
	int map_length;
	int start_lives = 3;
	int start_score = 0;
	prepare_the_map();
	i = 0;
	map_length = parse_map(&game_window.width, &game_window.height);
	game_window.assets = malloc(sizeof(struct asset) * map_length);
	game_window.mlx = mlx_init();
	game_window.mlx_window = mlx_new_window(game_window.mlx, game_window.width, game_window.height, "The Game");
	game_window.column = 0;
	game_window.row = 0;
	map = open("./maps/map.ber", O_RDONLY);
	while (i < map_length)
	{
		read(map, &map_value, 1);
		if (map_value_validation(map_value))
		{
			game_window.assets[i].height = 20;
			game_window.assets[i].width = 20;
			game_window.assets[i].asset_object = mlx_xpm_file_to_image(game_window.mlx, put_the_img(map_value), &game_window.assets[i].height, &game_window.assets[i].width);
			if (map_value == 'P')
			{
				game_window.hero.y = game_window.row;
				game_window.hero.x = game_window.column;
			}
			mlx_put_image_to_window(game_window.mlx, game_window.mlx_window, game_window.assets[i].asset_object, game_window.column, game_window.row);
			game_window.column += 20;
			i++;
		}
		else
		{
			game_window.row += 20;
			game_window.column = 0;
		}
		create_player(&game_window, &start_lives, &start_score);
	}
	close(map);
	mlx_key_hook(game_window.mlx_window, close_the_window, &game_window);
	mlx_loop(game_window.mlx);
	return 0;
}
