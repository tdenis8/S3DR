#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <functional>
#include <map>
#include <vector>
#include <utility> // for std::forward

/// Class encapusulates information associated with an event,
class EventInfo {
    public:
        EventInfo()=default;
        virtual ~EventInfo() {};
};

template <typename EventType>
class Subject {
    public:
        Subject(): event_id_counter(0) {};
        Subject(const Subject&)=delete;
        Subject& operator=(const Subject&)=delete;
        virtual ~Subject() {};

        template <typename Observer>
        unsigned int Observe(const EventType& event_type, Observer&& observer) {
            observers[event_type].push_back(std::make_pair(++event_id_counter, std::forward<Observer>(observer)));
            return event_id_counter;
        }

        void RemoveObserver(unsigned int event_id){
            for(auto & kv: observers){
                auto it=kv.second.begin();
                auto end=kv.second.end();
                for (; it!=end; ++it){
                    if(it->first==event_id){
                        kv.second.erase(it);
                        return;
                    }
                }
            }
        }

        void Emit(const EventType & event_type) const
        {
            if(!observers.count(event_type)){
                return;
            }
            
            for (const auto & it : observers.at(event_type)){
                it.second(EventInfo());
            }
        }

        void Emit(const EventType & event_type, const EventInfo & event_info) const
        {
            if(!observers.count(event_type)){
                return;
            }
            
            for (const auto & it : observers.at(event_type)){
                it.second(event_info);
            }
        }

    private:
        unsigned int event_id_counter;
        std::map<EventType, std::vector<std::pair<unsigned int, std::function<void(const EventInfo & )>>>> observers;

};

#endif 