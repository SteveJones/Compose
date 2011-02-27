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

Message::Message() {
  m_ref_headers = Gtk::ListStore::create(header_model());
  m_ref_body_buffer = Gtk::TextBuffer::create();
}

