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

sigc::signal<void, Glib::RefPtr<Compose::Message> > Compose::Compose::signal_send() {
  return pimpl->signal_send();
}

sigc::signal<void> Compose::Compose::signal_cancel() {
  return pimpl->signal_cancel();
}

void Compose::Compose::set_message(Glib::RefPtr<Message> message) {
  pimpl->set_message(message);
}

bool Compose::Compose::on_delete_event(GdkEventAny *event) {
  signal_cancel().emit();
  return true;
}
