/**********************************************************************************************************************************************************
*
*
*     __  ____            __  _         
*    /  |/  (_)___  ___  / /_(_)_______ 
*   / /|_/ / / __ \/ _ \/ __/ / ___/ _ \
*  / /  / / / / / /  __/ /_/ (__  )  __/
* /_/  /_/_/_/ /_/\___/\__/_/____/\___/ 
*                                      
**-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*
*	Minetise Library (c) Minetise 2018. 
*
*	Last Revision : Rev 1.0 21/04/2018
*
*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*
*   Rev 1.0 21/04/2018
*		Basic usage sample.
*
*       This sample demonstrate how to :
*
*			Initialise the Minetise SDK.
*			Retreive current hashrate on local host.
*			Terminate mining process.
*
*	Note: *only* Release configurations are valid as libMinetise libraries are shipping for release *only*.
*         (in other words Debug configurations are not able to compile properly.)
*
*************************************************************************************************************************************************************/
#include <conio.h>
#include <string>
#include "Minetise.h"

int main(void)
{
	double currentHashrate;

	bool working = false;

	std::string walletId = "42huHAgjC9KBPPfwxG4ujd9ZbZWX8fqndE8s76TdHtqeUebAvDvqhoESG4zUPtLrAwP6QdXyyABw2Gtf2iZf3GvaNMYrk4a";
	std::string poolAddr = "stratum+tcp://xmrpool.eu:3333";
	std::string password = "x";
	std::string appId = "TEST_APP";

	printf("\nBasic usage of libMinetise SDK...\n");
	printf("\nConnecting to %s...\n(It may take some time to start working, please wait...)\n",poolAddr.data());

	//All above informations must be correct for a successful initialisation. (MINING_CURRENCY and MINING_STRENGTH below are also the recommended settings)
	if (minetiseInit(walletId.data(), poolAddr.data(), password.data(), appId.data(), MINING_MONERO, MINING_LOW)) {

		//Main loop until keyboard stroke is detected.
		while (! _kbhit()) {

			//Retreiving current hash-power value..
			currentHashrate = minetiseGetHashrate();

			//If hashrate is != 0 we are connected to the pool.
			if ((int)currentHashrate > 0) {
				if (!working) {
					working = true;
					printf("\nWorking at %s\n", poolAddr.data());
				}
				printf("\nCurrent hashrate %f H/s",currentHashrate);
			}
			else {
				if (working) {
					working = false;
					printf("\nNot currently working at %s\n", poolAddr.data());
				}
			}
			
			//Current thread is going to sleep for 10 seconds until next loop.
			minetiseSleep(10.0f);

		}
		//Terminating mining process.
		minetiseQuit();
	}
	return 1;
}
