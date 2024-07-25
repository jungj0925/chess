#include "subject.h"
#include "observer.h"
#include <vector>


// Adding an observer to the given subject
void Subject::attach( Observer* o ) {
     // Add to the end of the vector
     observers.emplace_back(o);
}

// Removing an observer from a given subject
void Subject::detach( Observer* o ) {
     // Find the given Observer in the vector and erase
     for (auto it = observers.begin(); it != observers.end(); ++it) {
          if (*it == o) {
               it = observers.erase(it);
               break;
          }
     }
}


// Call the nofify method on all of the subject's observers
void Subject::notifyObservers() const {
     // Notify each individual Observer
     for (auto o : observers) o->notify();
}


// Destructor
Subject::~Subject() {
     // Delete each Observer
     for (auto o : observers) delete o; 
}
