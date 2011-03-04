#include "message.hpp"
#include <gtkmm.h>
#include <memory>
#include <algorithm>

using namespace Compose;

HeaderModelColumns::HeaderModelColumns() {
  add(m_name);
  add(m_value);
  add(m_shown);
}

static std::auto_ptr<HeaderModelColumns> ref_header_model;

const HeaderModelColumns &Compose::header_model() {
  if (!ref_header_model.get())
    ref_header_model = std::auto_ptr<HeaderModelColumns>(new HeaderModelColumns());
  return *ref_header_model;
}

Message::Message()
  : ObjectBase("Message")
{
  m_ref_headers = Gtk::ListStore::create(header_model());
  m_ref_visible_headers = Gtk::TreeModelFilter::create(m_ref_headers);
  m_ref_visible_headers->set_visible_column(header_model().m_shown);
  m_ref_body_buffer = Gtk::TextBuffer::create();
}

void Message::connect_header_edited(Glib::SignalProxy2<void, 
				    const Glib::ustring &, const Glib::ustring &> signal) {
  signal.connect(sigc::mem_fun(*this, &Message::on_header_edited));
}

void Message::on_header_edited(const Glib::ustring &path, const Glib::ustring &value) {
  Gtk::ListStore::iterator row_iter = m_ref_headers->get_iter(path);
  (*row_iter)[header_model().m_value] = value;
}

Message::visible_header_setter::visible_header_setter(const Glib::ustring &name, bool value)
  : m_name(name.lowercase()),
    m_value(value)
{}

void Message::visible_header_setter::operator ()(Gtk::TreeIter row) const {
  Glib::ustring name = (*row)[header_model().m_name];
  if (m_name == "" || name.lowercase() == m_name)
    (*row)[header_model().m_shown] = m_value;
}

void Message::set_header_visible(const Glib::ustring &name, bool value) {
  Gtk::ListStore::Children children = m_ref_headers->children();
  std::for_each(children.begin(), children.end(), visible_header_setter(name, value));
}

void Message::set_headers_visible(bool value) {
  Gtk::ListStore::Children children = m_ref_headers->children();
  std::for_each(children.begin(), children.end(), visible_header_setter("", value));
}

