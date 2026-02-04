#include<ncurses.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#define INCOMPLETE 1
#define COMPLETE 2
#define ERROR 3


bool isBs(char c)
{
	switch(c)
	{
		case KEY_BACKSPACE:
		case 127:
		case '\b':
			return true;
		break;
	}
	return false;
}

int wc(char* ch)
{
	int i = 0;
	int count = 1;
	while(ch[i] != '\0')
	{
		if(ch[i] == ' ')
		{
			count++;
		}
		i++;
	}
	return count;
}

int main(int argc, char** argv) {
	// Initialize the ncurses mode
	initscr();            
	cbreak();
	noecho();
	
	//init colors

	start_color();
	init_pair(INCOMPLETE, COLOR_BLUE, COLOR_BLACK);
	init_pair(COMPLETE, COLOR_YELLOW, COLOR_BLACK);
	init_pair(ERROR, COLOR_BLACK, COLOR_RED);


	//get cursor out way
	//doesnt work tho cause fuck me
	refresh();

	//inital time and # of quotes
	int nQuotes = 1;
	if(argv[1])
	{
		nQuotes = atoi(argv[1]);
	}
	int iTime = 0;
	int wCount = 0;
	for(int j = 0; j < nQuotes; j++)
	{
		//get line from file
		FILE* f = fopen("/home/liam/projects/typetest/quotes.txt", "r");


		char line[1024];
		//go thru random number o lines
		srand(time(NULL));
		for(int z = 0; z < rand() % 162 + 1; z++)
		{
			fgets(line, 1024, f);
		}
		wCount += wc(line);
		int i = 0;
		int e = 0;
		char* incomplete = line;
		char complete[1024];
		char error[1024];
		for(;;)
		{
			//inital render
			attron(COLOR_PAIR(INCOMPLETE));
			mvprintw(LINES / 2, 0+i+e, incomplete);
			refresh();           
			char in = getch();
			if(!isBs(in))
			{

				if(in == line[i])
				{
					complete[i] = in;
					i++;
				}
				else
				{
					error[e] = in;
					e++;
				}
					incomplete++;

			}
			else if(isBs(in))
			{
				if(e > 0)
				{
					error[e] = '\0';
					e--;
					incomplete--;
				}
				else
				{
					complete[i] = '\0';
					i--;
					incomplete--;
				}
			}
			attron(COLOR_PAIR(COMPLETE));
			mvprintw(LINES / 2, 0, complete);
			attron(COLOR_PAIR(ERROR));
			mvprintw(LINES / 2, 0+i, error);
			attron(COLOR_PAIR(INCOMPLETE));
			mvprintw(LINES / 2, 0+i+e, incomplete);
			move(LINES / 2 - 4, (COLS-20) / 2);
			refresh();           
			move(LINES / 2 - 4, (COLS-20) / 2);
			if(iTime == 0)
			{
				iTime = time(NULL);
			}
			
			//end condition
			if(incomplete[0] == '\0')
			{
				break;
			}
		}
		clear();
	}
	int fTime = time(NULL);

	fTime -= iTime;

	endwin();            
	printf("%f\n", ((float)wCount) / ((float)fTime / 60.0));

	return 0;
}
