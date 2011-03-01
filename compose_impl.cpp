#include "message.hpp"
#include "compose_impl.hpp"
#include <gtkmm/window.h>

using namespace Compose;

ComposeImpl::ComposeImpl(Gtk::Window *parent)
  : m_parent(parent)
{
  m_parent->set_title("Compose");
  m_parent->set_default_size(500, 650);

  m_header_window.add(m_header_view);
  m_header_window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  m_paned.pack1(m_header_window, true, true);

  m_body_view.set_wrap_mode(Gtk::WRAP_WORD);
  m_body_window.add(m_body_view);
  m_body_window.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_ALWAYS);
  m_paned.pack2(m_body_window, true, false);

  m_paned.set_position(200);
  m_box.pack_start(m_paned);

  m_parent->add(m_box);
  
  m_parent->show_all_children();
}

void ComposeImpl::set_message(Glib::RefPtr<Message> message) {
  m_ref_message = message;
  m_body_view.set_buffer(m_ref_message->m_ref_body_buffer);
  m_header_view.set_message(message);
}
