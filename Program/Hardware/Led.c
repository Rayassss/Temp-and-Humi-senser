#include "STC8F.h"
#include "Led.h"
void Ledinit(unsigned char i)
{
	if(i == 1)
	{
		Led = 0;
	}
	else if(i == 0)
	{
		Led = 1;
	}
}
	