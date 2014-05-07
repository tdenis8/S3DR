#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <functional>
#include <utility>
#include <map>
#include <vector>

class Observer {
public:
    Observer();
    virtual ~Observer();

    unsigned int Id() const;

private:
    unsigned int observer_id;
};

// Class encapusulates information associated with an event,
class EventInfo {
public:
    EventInfo() = default;
    virtual ~EventInfo(){};
};

template <typename EventType> class Subject {
public:
    Subject()
        : event_id_counter(0){};
    Subject(const Subject&) = delete;
    Subject& operator=(const Subject&) = delete;
    virtual ~Subject(){};

    template <typename FunctionObjectType>
    unsigned int Observe(const EventType& event_type, FunctionObjectType&& function_object)
    {
        function_objects[event_type].push_back(
            std::make_pair(++event_id_counter, std::forward<FunctionObjectType>(function_object)));
        return event_id_counter;
    }

    template <typename FunctionObjectType>
    unsigned int Observe(const EventType& event_type, FunctionObjectType&& function_object, const Observer* observer)
    {
        function_objects[event_type].push_back(
            std::make_pair(++event_id_counter, std::forward<FunctionObjectType>(function_object)));
        unsigned int observer_id = observer->Id();
        observers[observer_id].push_back(event_id_counter);
        return event_id_counter;
    }

    void RemoveObserver(unsigned int event_id)
    {
        for (auto& kv : function_objects) {
            auto it = kv.second.begin();
            auto end = kv.second.end();
            for (; it != end; ++it) {
                if (it->first == event_id) {
                    kv.second.erase(it);
                    return;
                }
            }
        }
    }

    void RemoveObservers(const Observer* observer)
    {
        unsigned int observer_id = observer->Id();
        if (!observers.count(observer_id)) {
            return;
        }

        auto& event_ids = observers[observer_id];
        for (unsigned int event_id : event_ids) {
            RemoveObserver(event_id);
        }
        observers.erase(observer_id);
    }

    void Emit(const EventType& event_type) const
    {
        if (!function_objects.count(event_type)) {
            return;
        }

        for (const auto& it : function_objects.at(event_type)) {
            it.second(EventInfo());
        }
    }

    void Emit(const EventType& event_type, const EventInfo& event_info) const
    {
        if (!function_objects.count(event_type)) {
            return;
        }

        for (const auto& it : function_objects.at(event_type)) {
            it.second(event_info);
        }
    }

private:
    unsigned int event_id_counter;
    std::map<EventType, std::vector<std::pair<unsigned int, std::function<void(const EventInfo&)>>>> function_objects;
    std::map<unsigned int, std::vector<unsigned int>> observers;
};

#endif