/*
*DESCRIPTION: Its just a fun program to be used as an exercise. The program
*takes in input the length of an n x n array. Then it fills this square
*according to the option provided.
*
*LOGIC: Fill the buffer. Display the buffer. For the horizontal and vertical
*fill, its pretty simple. Just iterate and fill. For Spiral fill, oh yeah, its
*tricky. Use recursion. Just fill the outer edge, and then pass the size as 
*(n - 2) to the recursive call. The x and y keep track of the location in the 
*buffer and count_spiral is the count you're filling in it.
*
*AUTHOR:	Faiz Kothari
*EMAIL:		faiz.off93@gmail.com
*VERSION:	1.0
*
*TODO: 
*1. In the function buff_init() there is no check if malloc() returns NULL
*2. Modularize the code. Make a library of pattern filling.
*3. Do a Valgrind check.
*/

//INCLUDES
#include <stdio.h>
#include <stdlib.h>

//DEFINE AND TYPEDEF
typedef void (*fill)(int, int **);

//PROTOTYPES
void buf_init(int, int ***);
void buf_free(int, int ***);
void fill_buf(int **, int, fill);
void draw_buf(int, int **);
void call_exit(void);
void spiral(int, int **);
void horizontal(int, int **);
void vertical(int, int **);

//GLOBAL DATA
static int count_spiral = 1; 
static int x = 0;
static int y = 0;

//THE CODE
int main(int argc, char **argv)
{
	int n;
	int choice;
	int **buf = NULL;

choose_length:
	printf("Enter the Length of one side of the sqaure: ");
	scanf("%d",&n);
	if( n <= 0){
		printf("The size is Zero or Negative, Don't mess with me! :x\n");
		exit(0);
	}
	
wrong_choice:
	printf("Enter Your Choice: \n");
	printf("1 for Horizontal fill\n");
	printf("2 for Vertical fill\n");
	printf("3 for Spiral fill\n");
	printf("4 to Enter size again\n");
	printf("5 to Quit\n:");
	scanf("%d",&choice);
	
	switch(choice){
		case 1:
			buf_init(n,&buf);
			fill_buf(buf,n,horizontal);
			draw_buf(n,buf);
			buf_free(n,&buf);
			goto wrong_choice;
		
		case 2:
			buf_init(n,&buf);
			fill_buf(buf,n,vertical);
			draw_buf(n,buf);
			buf_free(n,&buf);
			goto wrong_choice;

		case 3:
			buf_init(n,&buf);
			fill_buf(buf,n,spiral);
			draw_buf(n,buf);
			buf_free(n,&buf);
			goto wrong_choice;

		case 4:
			goto choose_length;

		case 5:
			exit(0);			

		default:
			goto wrong_choice;
			
	}
	fill_buf(buf,n,spiral);
	draw_buf(n,buf);
}
void buf_init(int n, int ***buf)
{
	*buf = (int **)malloc(n*sizeof(int *));
	if((*buf) == 0)
		call_exit();
	else{
		int i = 0;
		while(i < n){
			(*buf)[i] = (int *)malloc(n*sizeof(int));
			i++;
		}
	}
}
void buf_free(int n, int ***buf)
{
	int i = 0;
	while(i < n){
		free((*buf)[i]);
		i++;
	}
	free((*buf));
	*buf = NULL;
	x = 0;
	y = 0;
	count_spiral = 1;
	return;
}
void call_exit(void)
{
	printf("Something went wrong. Terminating.\n");
	exit(1);
}
void fill_buf(int **buf, int n, fill p)
{
	p(n, buf);
}
void draw_buf(int n, int **buf)
{
	int i,j;
	int row = n;
	int col = n;
	printf("\nThe %d x %d looks like :\n\n", n, n);
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			printf("%3d ",buf[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void vertical(int n, int **buf)
{
	int i, j;
	int count = 1;
	for(j = 0; j < n; j++){
		for(i = 0; i < n; i++){
			buf[i][j] = count;
			count++;
		}
	}
}
void horizontal(int n, int **buf)
{
	int i,j;
	int count = 1;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			buf[i][j] = count;
			count++;
		}
	}
}
void spiral(int n, int **buf)
{
	if(n <= 0)
		return;
	else if( n == 1){
		buf[x][y] = count_spiral;
		return;
	}
	else{
		int ini_x = x;
		int ini_y = y;
		//printf("x = %d, y = %d\n", x, y);
		for(; x < n + ini_x; x++, count_spiral++) //TL to TR
			buf[y][x] = count_spiral;
		for(x = x - 1, y = y + 1; y < n + ini_y; y++, count_spiral++) //TR to BR
			buf[y][x] = count_spiral;
		for(x = x - 1, y = y - 1; x >= ini_x; x--, count_spiral++) //BR to BL
			buf[y][x] = count_spiral;
		for(x = x + 1, y = y - 1; y > ini_y; y--, count_spiral++) //BL to TL
			buf[y][x] = count_spiral;
		
		y++;
		x++;

		//printf("x = %d, y = %d\n", x, y);
		spiral(n - 2, buf);
	}
}