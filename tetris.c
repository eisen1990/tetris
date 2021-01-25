#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

int kbhit(char *key);

typedef struct _pos{
	int x;
	int y;
}POS;

void init_pos(POS *p)
{
	p->x = 20;
	p->y = 20;
}

int main(void)
{
	char key = '\0';
	int i = 0;
	POS pos;
	init_pos(&pos);
	system("clear");
	while(1)
	{
		if(kbhit(&key))
		{
			system("clear");
			if(key == 'k')
				pos.y++;
			else if(key == 'j')
				pos.y--;
			else ;
			for(i=0; i < pos.y; i++)
				printf("\n");
			printf("ㅁ");
			//printf("%c\n",key);
            // foo bar test2
		}
		  
		//usleep(100*1000);
	}
	return 0;
}

int kbhit(char *key)
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();
	*key = ch;

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF)
	{
		//ungetc(ch, stdin); //ungetc : against a new key. maintaining the key buffer 
		return 1;
	}

	return 0;
}
