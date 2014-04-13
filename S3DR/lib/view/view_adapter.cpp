#include "view_adapter.hpp"

#include "view.hpp"

ViewAdapter::ViewAdapter(View & view):
	view(view)
{

}

ViewAdapter::~ViewAdapter(){

}

const ViewSettings & ViewAdapter::ViewSettingsRef() const {
	return view.ViewSettingsRef();
}