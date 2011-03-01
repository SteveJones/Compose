#include "compose.hpp"
#include "message.hpp"

Compose::Compose::Compose()
  : Gtk::Window()
{
  set_title("Compose");
  set_default_size(500, 650);
  
  m_ref_value_cell = Gtk::manage(new Gtk::CellRendererText());
  m_ref_value_cell->property_wrap_mode().set_value(Pango::WRAP_WORD);
  m_ref_value_cell->property_editable().set_value(true);
  m_header_view.append_column("Header", header_model().m_name);
  m_header_view.append_column("Value", *m_ref_value_cell);
  m_header_view.get_column(1)->add_attribute(m_ref_value_cell->property_text(),
					     header_model().m_value);
  m_header_view.set_headers_visible(false);

  m_header_window.add(m_header_view);
  m_header_window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  m_paned.pack1(m_header_window, true, true);

  m_body_view.set_wrap_mode(Gtk::WRAP_WORD);
  m_body_window.add(m_body_view);
  m_body_window.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_ALWAYS);
  m_paned.pack2(m_body_window, true, false);

  m_paned.set_position(200);
  m_box.pack_start(m_paned);

  add(m_box);

  show_all_children();
}

void Compose::Compose::set_message(Glib::RefPtr<Message> message) {
  m_ref_message = message;
  m_header_view.set_model(m_ref_message->m_ref_headers);
  m_body_view.set_buffer(m_ref_message->m_ref_body_buffer);
  m_ref_message->connect_header_edited(m_ref_value_cell->signal_edited());
}
