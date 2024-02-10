#ifndef CTHREAD_H_
#define CTHREAD_H

#include <QThread>

#include "cInformationstag.h"

class cThread : public QThread
{
public:
 	// zum initialisieren
 	void setInformationstag(cInformationstag * informationstag) { itsInformationstag = informationstag; }
 	void setOptimal(bool optimal) { itsOptimal = optimal; };
 	
    void run();  // wird ausgefuhert wenn der Thread gestartet wird

private:

	cInformationstag * itsInformationstag;
	bool itsOptimal;
	
};

 
#endif /*CTHREAD_H_*/
