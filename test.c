#include <mlx.h>
#include<fcntl.h> 
#include <stdio.h>
#include<stdlib.h> 
#include<unistd.h> 

struct b{
    int x;
};

struct a{
    struct b *list;
};

int main(void){
    struct a my;
    int i = 0;
    my.list = malloc(sizeof(struct b)*4);
    while(i<4){
        my.list[i].x=i;
        i++; 
    }
    i = 0;
    while(i<4)
    {
        printf("%d",my.list[i].x);
        i++;
    }
    return 0;
}