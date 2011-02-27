#ifndef __message_parser_hpp
#define __message_parser_hpp

#include "message.hpp"
#include <stdexcept>
#include <locale>
#include <iterator>

#include <iostream>

namespace Compose {

  template<class CharT>
  bool is_ftext(CharT c) {
    return (c >= 33 && c <= 57) || (c >= 59 && c <= 126);
  }

  template<class InputIterator>
  InputIterator expect(InputIterator begin, InputIterator end, char c) {
    if (begin == end) {
      throw std::runtime_error("Unexpected end of input");
    }
    if (*begin != c) {
      std::string error = "Expected '";
      error += c;
      error += "' found '";
      error += *begin;
      error += "'";
      throw std::runtime_error(error);
    }
    return ++begin;
  }

  template<class InputIterator, class OutputIterator>
  InputIterator parse_header_field(InputIterator begin, InputIterator end, OutputIterator out) {
    while (begin != end && is_ftext(*begin)) {
      *out++ = *begin++;
    }
    begin = expect(begin, end, ':');
    return begin;
  }

  template<class InputIterator>
  InputIterator skip_ws(InputIterator begin, InputIterator end) {
    while (begin != end && (*begin == ' ' || *begin == '\t')) {
      ++begin;
    }
    return begin;
  }

  template<class InputIterator, class OutputIterator>
  InputIterator parse_header_field_value(InputIterator begin, InputIterator end,
					 OutputIterator out) {
    do {
      while (begin != end && *begin != '\n') {
	*out++ = *begin++;
      }
      begin = expect(begin, end, '\n');
    } while (begin != end && (*begin == ' ' || *begin == '\t'));
    return begin;
  }  

  template<class InputIterator>
  void parse_message(InputIterator begin, InputIterator end, Glib::RefPtr<Message> message) {
    Gtk::TreeModel::Row row;

    try {
      while (begin != end && *begin != '\n') {
	Glib::ustring name, value;
	begin = parse_header_field(begin, end, std::back_inserter(name));
	begin = skip_ws(begin, end);
	begin = parse_header_field_value(begin, end, std::back_inserter(value));
	row = *(message->m_ref_headers->append());
	row[header_model().m_name] = name;
	row[header_model().m_value] = value;
      }
      if (begin != end) {
	++begin;
      }
      Glib::ustring body;
      copy(begin, end, std::back_inserter(body));
      message->m_ref_body_buffer->set_text(body);
    } catch (std::exception e) {
      copy(begin, end, std::ostream_iterator<char>(std::cout));
      std::cout.flush();
      throw e;
    }
  }

}

#endif
