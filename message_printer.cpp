#include "message_printer.hpp"

#include <iostream>

using namespace Compose;

class HeaderPrinter {
  std::ostream &m_os;
public:
  explicit HeaderPrinter(std::ostream &os)
    : m_os(os)
  {}

  void operator ()(const Gtk::TreeModel::iterator &i) {
    Gtk::TreeRow row = *i;
    int pos = 0;
    Glib::ustring name = row[header_model().m_name];
    m_os << name << ":";
    pos += name.length() + 1;
    Glib::ustring value = row[header_model().m_value];

    Glib::ustring::size_type start;
    Glib::ustring::size_type end = 0;
    do {
      start = value.find_first_not_of(" \t", end);
      end = value.find_first_of(" \t", start);

      if (end > value.length()) // OMGWTFBBQ
	end = value.length();

      if (end - start == 0)
	continue;

      if (pos + (end - start) + 1 > 78) {
	m_os << std::endl;
	pos = 0;
      }
      m_os << " " << value.substr(start, end - start);
      pos += (end - start) + 1;
    } while (end < value.length());

    m_os << std::endl;
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
