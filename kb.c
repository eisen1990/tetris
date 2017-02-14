#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
int kbhit(void)
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
	int t = 0;
	system("clear");
	while(1)
	{
		if(kbhit())
		{
			system("clear");
			t = 0;
		}
		  
		printf("%d\n",t++);
		usleep(100*1000);
	}
	return 0;
}
