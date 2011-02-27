#include "compose.hpp"
#include "message.hpp"
#include "message_parser.hpp"
#include <iterator>
#include <iostream>
#include <gtkmm/main.h>

int main(int argc, char *argv[]) {
  Gtk::Main kit(argc, argv);

  Compose::Compose compose;

  Glib::RefPtr<Compose::Message> message(new Compose::Message());
  std::cin.unsetf(std::ios_base::skipws);
  parse_message(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(), message);
  compose.set_message(message);

  Gtk::Main::run(compose);
}
