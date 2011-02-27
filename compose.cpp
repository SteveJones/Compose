#include "compose.hpp"
#include "message.hpp"

Compose::Compose::Compose()
  : Gtk::Window()
{
  set_title("Compose");
  m_box.pack_start(m_header_view, Gtk::PACK_SHRINK, 0);
  m_box.pack_start(m_body_view);
  m_header_view.append_column("Header", header_model().m_name);
  m_header_view.append_column("Value", header_model().m_value);
  add(m_box);
  show_all_children();
}

void Compose::Compose::set_message(Glib::RefPtr<Message> message) {
  m_ref_message = message;
  m_header_view.set_model(m_ref_message->m_ref_headers);
  m_body_view.set_buffer(m_ref_message->m_ref_body_buffer);
}
