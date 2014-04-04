#ifndef _SELECTION_SET_H_
#define _SELECTION_SET_H_

#include "utility/subject.hpp"

enum class SelectionSetEvent : unsigned int { CALCULATE_SELECTION };

struct SelectionData {
    unsigned int scene_object_key = 0;
    unsigned int entry_index = 0;
    unsigned int primitive_id = 0;
};

class SelectionInfo: public EventInfo {
    public:
        SelectionInfo(int x, int y) : 
            EventInfo(),  x(x), y(y) {}
        
        const int & X() const { return x; }
        const int & Y() const { return y; }

    private:
        int x;
        int y;
};

class SelectionSet : public Subject<SelectionSetEvent> {
    public:
    	SelectionSet();
        SelectionSet(const SelectionSet &)=delete;
        SelectionSet & operator=(const SelectionSet &)=delete;
        virtual ~SelectionSet();

        SelectionData GetSelectionData() const;
        void SetSelectionData(const SelectionData & selection_data);
    	void CalculateSelection(int x, int y);

    protected:         
        SelectionData selection_data; 	
};

#endif