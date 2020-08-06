#include "STC8F.h"
#include "Led.h"
sbit Led = P2^2;
void Ledinit()
{
	Led = 0;
}