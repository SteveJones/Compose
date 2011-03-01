#include "message.hpp"
#include "compose.hpp"
#include "compose_impl.hpp"

Compose::Compose::Compose()
  : Gtk::Window()
{
  pimpl = std::auto_ptr<ComposeImpl>(new ComposeImpl(this));
}

Compose::Compose::~Compose() {
}

void Compose::Compose::set_message(Glib::RefPtr<Message> message) {
  pimpl->set_message(message);
}
