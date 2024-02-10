#include "cThread.h"

void cThread::run()
{  
	itsInformationstag->PlanErstellen(itsOptimal);

    cout << "BERECHNUNGEN FERTIG!!!" << endl;
}
