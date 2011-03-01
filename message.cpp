#include "message.hpp"
#include <memory>

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

