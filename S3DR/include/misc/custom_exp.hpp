#ifndef _CUSTOM_EXP_H_
#define _CUSTOM_EXP_H_

#include <exception>
#include <string>

class CustomExp: public std::exception {
    public:
        CustomExp(const std::string & message) : message(message) {};
        ~CustomExp() noexcept {};
        
      	virtual const char* what() noexcept
      	{
        	return message.c_str();
      	}
  	
  	private:
  	    std::string message; 
};

#endif
