#include "compose.hpp"
#include "message.hpp"

int main(int argc, char *argv[]) {
  Gtk::Main kit(argc, argv);

  Compose::Compose compose;

  Glib::RefPtr<Compose::Message> message(new Compose::Message());
  compose.set_message(message);

  Gtk::Main::run(compose);
}
