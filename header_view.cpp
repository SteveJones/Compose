#include "message.hpp"
#include "header_view.hpp"
#include "header_view_impl.hpp"

using namespace Compose;

HeaderView::HeaderView()
  : Gtk::TreeView()
{
  pimpl = std::auto_ptr<HeaderViewImpl>(new HeaderViewImpl(this));
}

void HeaderView::set_message(Glib::RefPtr<Message> message) {
  pimpl->set_message(message);
}

