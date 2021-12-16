#ifndef __LUNCH__
#define __LUNCH__

typedef struct lunch_t
{
	char sendwich[20];
	int	 fruit;
	int	 drink;
}Lunch;

void initLunch(Lunch* pLaunch);
void printLunch(const Lunch* pLaunch);

#endif