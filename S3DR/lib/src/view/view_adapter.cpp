#include "view_adapter.hpp"

#include "view.hpp"

ViewAdapter::ViewAdapter(View &view) : view_(view), camera_(view.GetCamera()), view_settings_(view.GetViewSettings())
{
}

ViewAdapter::~ViewAdapter()
{
}
