#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define CLEAR "\033[H\033[J"
#define CURSOR_OFF "\033[?25l"
#define CURSOR_ON "\033[?25h"

#ifdef _WIN32 
#define CHARACTER "\xDB"
#else
#define CHARACTER "\u2588"
#endif

#define DIGITS 8
#define DIGIT_SIZE (FONT_WIDTH * FONT_HEIGHT)
#define FONT_HEIGHT 8
#define FONT_WIDTH 8

static const unsigned char font[11 * DIGIT_SIZE] = {
	0,1,1,1,1,1,1,0,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	0,1,1,1,1,1,1,0,
	0,0,0,1,1,0,0,0,
	0,0,1,1,1,0,0,0,
	0,1,1,1,1,0,0,0,
	0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,
	0,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,0,
	1,1,0,0,0,0,1,1,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,1,1,0,
	0,0,0,0,1,1,0,0,
	0,0,0,1,1,0,0,0,
	0,0,1,1,0,0,0,0,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,1,1,
	0,1,1,1,1,1,1,0,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,1,1,
	1,1,1,1,1,1,1,0,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	0,1,1,1,1,1,1,1,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,1,1,
	1,1,1,1,1,1,1,1,
	1,1,0,0,0,0,0,0,
	1,1,0,0,0,0,0,0,
	1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,1,1,
	1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,0,
	1,1,0,0,0,0,0,0,
	1,1,0,0,0,0,0,0,
	1,1,1,1,1,1,1,0,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	0,1,1,1,1,1,1,0,
	1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,1,1,
	0,0,1,1,1,1,1,1,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,1,1,
	0,1,1,1,1,1,1,0,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	0,1,1,1,1,1,1,0,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	0,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,0,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,
	0,1,1,1,1,1,1,1,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,1,1,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

void drawclock(struct tm *tm){
	unsigned char clock[DIGITS] = {
		tm->tm_hour / 10,
		tm->tm_hour % 10,
		10,
		tm->tm_min / 10,
		tm->tm_min % 10,
		10,
		tm->tm_sec / 10,
		tm->tm_sec % 10
	};

	printf(CLEAR);

	for(unsigned char row = 0; row < FONT_HEIGHT; row++){
		for(unsigned char digit = 0; digit < DIGITS; digit++){
			for(unsigned char col = 0; col < FONT_WIDTH; col++){
				if(font[clock[digit] * DIGIT_SIZE + row * FONT_WIDTH + col]){
					printf("%s", CHARACTER);
				}else{
					printf(" ");
				}
			}
			printf(" ");
		}
		printf("\n");
	}
}

void signalhandler(int signalnum){
	(void)signalnum;
	printf(CURSOR_ON);
	exit(0);
}

int main(void){
	time_t now;

	signal(SIGINT, signalhandler);
	printf(CURSOR_OFF);
	printf(CLEAR);

	while(1){
		time(&now);
		drawclock(localtime(&now));
		sleep(1);
	}

	return 0;
}
