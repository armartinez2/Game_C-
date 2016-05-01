#pragma once
#include "stdafx.h"
#include "background.hpp"

using namespace std;

class ThreadedOutClass 
{ /*Beginning of class=====================================*/

public: 
	int microseconds = 1000000;	
	void RunThread()
	{
		for(;;)
		{
			usleep(microseconds);
			//In here should be a loop for Alex's new controls
			cout << "go" << endl;
		}
	}

	

/*end of class=============================================*/
};