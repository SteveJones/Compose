#include "compose.hpp"
#include "message.hpp"
#include "message_parser.hpp"
#include "message_printer.hpp"

#include <iterator>
#include <iostream>
#include <fstream>
#include <gtkmm/main.h>

int main(int argc, char *argv[]) {
  Gtk::Main kit(argc, argv);

  Compose::Compose compose;

  Glib::RefPtr<Compose::Message> message(new Compose::Message());

  if (argc < 2) {
    std::cin.unsetf(std::ios_base::skipws);
    parse_message(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(), message);
  } else {
    std::ifstream infile(argv[1]);
    infile.unsetf(std::ios_base::skipws);
    parse_message(std::istream_iterator<char>(infile), std::istream_iterator<char>(), message);
  }

  compose.set_message(message);

  Gtk::Main::run(compose);

  if (argc < 2) {
    std::cout << message;
  } else {
    std::ofstream outfile(argv[1]);
    outfile << message;
    outfile.flush();
  }

}
