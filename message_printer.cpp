#include "message_printer.hpp"

#include <ostream>

using namespace Compose;

class HeaderPrinter {
  std::ostream &m_os;
public:
  explicit HeaderPrinter(std::ostream &os)
    : m_os(os)
  {}

  void operator ()(const Gtk::TreeModel::iterator &i) {
    Gtk::TreeRow row = *i;
    m_os << row[header_model().m_name] << ": " << row[header_model().m_value] << std::endl;
   }
};

std::ostream &Compose::operator <<(std::ostream &os, Glib::RefPtr<Message> message) {
  HeaderPrinter header_printer(os);
  Gtk::TreeModel::iterator i = message->m_ref_headers->get_iter("0");
  while (i) {
    header_printer(i);
    ++i;
  }
  os << std::endl;
  os << message->m_ref_body_buffer->get_text();
  return os;
}
