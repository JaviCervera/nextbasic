#ifndef GUIEVENT_H
#define GUIEVENT_H

#define EVENT_INIT	1
#define EVENT_MENU	2

// Event handler
typedef void (*wxEventHandler)(int,void*,int);

// Used internally by other modules, implemented in "app.cpp"
extern wxEventHandler _nb_eventHandler;

#endif // GUIEVENT_H