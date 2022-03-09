#pragma once

class Event {

protected:
	double timestamp;

public:

	Event(double timestamp) ;
	virtual void run() = 0;

	double getTimestamp();
	/*{
		return this->timestamp;
	}*/
};
