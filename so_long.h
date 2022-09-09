#ifndef SO_LONG_H
#define SO_LONG_H
#include "./minilibx/mlx.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include "get_next_line/get_next_line.h"

struct player
{
    void *object;
    char *asset;
    int x;
    int y;
    int size;
    int *scores;
    int *lives;
};

struct free_space
{
    void *object;
};

struct asset
{
    void *asset_object;
    int height;
    int width;
    int column;
    int row;
};
struct window
{
    struct asset *assets;
    struct player hero;
    void *mlx;
    void *mlx_window;
    int width;
    int height;
    int column;
    int row;
};

#endif