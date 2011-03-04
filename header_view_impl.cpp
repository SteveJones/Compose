#include "header_view_impl.hpp"
#include "message.hpp"
#include <gtkmm/treeview.h>

using namespace Compose;

HeaderViewImpl::HeaderViewImpl(Gtk::TreeView *parent)
  : m_parent(parent)
{
  m_parent->append_column("Header", header_model().m_name);
  m_parent->append_column_editable("Value", header_model().m_value);
  m_ref_value_cell = dynamic_cast<Gtk::CellRendererText *>(m_parent->get_column_cell_renderer(1));
  m_parent->set_headers_visible(false);
}

void HeaderViewImpl::set_message(Glib::RefPtr<Message> message) {
  m_ref_message = message;
  m_parent->set_model(m_ref_message->m_ref_visible_headers);
  m_ref_message->connect_header_edited(m_ref_value_cell->signal_edited());
}
