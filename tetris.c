#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
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

int main(void)
{
	char key = '\0';
	system("clear");
	while(1)
	{
		if(kbhit(&key))
		{
			system("clear");
			if(key == 'k')
				printf("1\n");
			else if(key == 'j')
				printf("2\n");
			else ;
			//printf("%c\n",key);
		}
		  
		//usleep(100*1000);
	}
	return 0;
}
