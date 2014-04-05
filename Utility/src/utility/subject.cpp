#include "subject.hpp"

static unsigned int __unique_observer_id_counter__ = 0;

Observer::Observer(){
	observer_id =  __unique_observer_id_counter__++;
}

Observer::~Observer(){

}

unsigned int Observer::Id() const {
	return observer_id;
}