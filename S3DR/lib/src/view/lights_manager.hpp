#ifndef _LIGHTS_MANAGER_H_
#define _LIGHTS_MANAGER_H_

#include "utility/subject.hpp"

#include "light.hpp"

enum class LightsManagerEvent : unsigned int
{
    LIGHT_ADDED,
};

class LightsManager : public Subject<LightsManagerEvent>
{
    public:
    LightsManager();
    LightsManager(const LightsManager&) = delete;
    LightsManager& operator=(const LightsManager&) = delete;
    virtual ~LightsManager();

    private:
};

#endif
