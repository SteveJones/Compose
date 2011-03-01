#include "header_view_impl.hpp"
#include "message.hpp"
#include <gtkmm/treeview.h>

using namespace Compose;

HeaderViewImpl::HeaderViewImpl(Gtk::TreeView *parent)
  : m_parent(parent)
{
  m_ref_value_cell = Gtk::manage(new Gtk::CellRendererText());
  m_ref_value_cell->property_wrap_mode().set_value(Pango::WRAP_WORD);
  m_ref_value_cell->property_editable().set_value(true);
  m_parent->append_column("Header", header_model().m_name);
  m_parent->append_column("Value", *m_ref_value_cell);
  m_parent->get_column(1)->add_attribute(m_ref_value_cell->property_text(),
					     header_model().m_value);
  m_parent->set_headers_visible(false);
}

void HeaderViewImpl::set_message(Glib::RefPtr<Message> message) {
  m_ref_message = message;
  m_parent->set_model(m_ref_message->m_ref_headers);
  m_ref_message->connect_header_edited(m_ref_value_cell->signal_edited());
}
