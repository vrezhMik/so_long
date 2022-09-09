ALL:
	gcc -lmlx -Lminilibx -framework OpenGL -framework AppKit  get_next_line/get_next_line.c get_next_line/get_next_line_utils.c main.c -o main  && ./main 