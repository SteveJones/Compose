#include "compose.hpp"
#include "message.hpp"
#include "message_parser.hpp"
#include "message_printer.hpp"

#include <iterator>
#include <iostream>
#include <fstream>
#include <gtkmm/main.h>
#include <gtkmm/messagedialog.h>

std::string out_file_name;
Compose::Compose *compose;

void save_message(Glib::RefPtr<Compose::Message> message) {
  std::ofstream ofs;

  if (out_file_name == "") {
    std::cout << message;
    compose->hide();
    return;
  }
  ofs.open(out_file_name.c_str(), std::ios_base::trunc);
  ofs << message;
  ofs.flush();
  ofs.close();

  compose->hide();
}

void cancel_message() {
  Gtk::MessageDialog dialog(*compose,
			    "Are you sure you want to cancel?", false,
			    Gtk::MESSAGE_QUESTION,
			    Gtk::BUTTONS_OK_CANCEL);
  dialog.set_secondary_text("All changes will be lost.");
  switch (dialog.run()) {
  case Gtk::RESPONSE_CANCEL:
    return;
  case Gtk::RESPONSE_OK:
    compose->hide();
    return;
  default:
    std::cerr << "cancel_message: unknown response from Gtk::MessageDialog" << std::endl;
  }
}

int main(int argc, char *argv[]) {
  Gtk::Main kit(argc, argv);

  Glib::RefPtr<Compose::Message> message(new Compose::Message());

  compose = new Compose::Compose();

  if (argc < 2) {
    std::cin.unsetf(std::ios_base::skipws);
    parse_message(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(), message);
  } else {
    std::ifstream infile(argv[1]);
    infile.unsetf(std::ios_base::skipws);
    parse_message(std::istream_iterator<char>(infile), std::istream_iterator<char>(), message);
    out_file_name = argv[1];
  }

  compose->set_message(message);
  compose->signal_send().connect(sigc::ptr_fun(save_message));
  compose->signal_cancel().connect(sigc::ptr_fun(cancel_message));

  Gtk::Main::run(*compose);

  Glib::Error::register_cleanup();
  Glib::wrap_register_cleanup();
  gdk_exit(0);
}
