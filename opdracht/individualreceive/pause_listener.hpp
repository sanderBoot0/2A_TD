#ifndef PAUSE_LISTENER_HPP
#define PAUSE_LISTENER_HPP

class pause_listener{
public:
	virtual void pause_detected(int pause_length) = 0;
};

#endif // PAUSE_LISTENER_HPP