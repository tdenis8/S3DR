#include "subject_tests.hpp"

#include "utility/subject.hpp"

#include <iostream>

// -------------------------------------------------------------
// Subject class
// -------------------------------------------------------------
enum class AEvent : unsigned int { SOMETHING_DONE, };

class A : public Subject<AEvent> {
  public:
        A();
        void DoSomething();
};

A::A():
	Subject() 
{
	std::cout<<__FUNCTION__<<std::endl;
}

void A::DoSomething(){
	std::cout<<__FUNCTION__<<std::endl;
	Emit(AEvent::SOMETHING_DONE);
}

// -------------------------------------------------------------
// Observer class
// -------------------------------------------------------------
class B : private Observer {
  	public:
    	B(A & a);
    	~B();

    private:
    	void SomethingDoneEventHandler(const EventInfo & info);

    	A & a;
};

B::B(A & a):
	Observer(),
	a(a)
{
	std::cout<<__FUNCTION__<<std::endl;
	a.Observe(AEvent::SOMETHING_DONE,
			  std::bind(&B::SomethingDoneEventHandler, this, std::placeholders::_1),
			  this);
}

B::~B(){
	std::cout<<__FUNCTION__<<std::endl;
	a.RemoveObservers(this);
}

void B::SomethingDoneEventHandler(const EventInfo & info){
	std::cout<<__FUNCTION__<<std::endl;
}

// -------------------------------------------------------------

bool TestSubject(){
	A a;
	B b(a);
	a.DoSomething();
}

void RunSubjectTests(){
    std::cout<<"Subject tests: "<<std::endl;
    auto all = true;
    if(all){
        TestSubject();
    }
    else{
        
    }
    std::cout<<std::endl;
}