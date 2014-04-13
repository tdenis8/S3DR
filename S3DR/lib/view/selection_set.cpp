#include "selection_set.hpp"

SelectionSet::SelectionSet():
	Subject()
{

}

SelectionSet::~SelectionSet(){

}

SelectionData SelectionSet::GetSelectionData() const{
	return selection_data;
}

void SelectionSet::SetSelectionData(const SelectionData & selection_data){
	this->selection_data = selection_data;
}

void SelectionSet::CalculateSelection(int x, int y){
	Emit(SelectionSetEvent::CALCULATE_SELECTION, SelectionInfo(x,y));
}