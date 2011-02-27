#ifndef __compose_compose_hpp
#define __compose_compose_hpp

#include <gtkmm.h>
#include "message.hpp"

namespace Compose {
  
  class Compose : public Gtk::Window {
  public:
    Compose();

    void set_message(Glib::RefPtr<Message> message);

  private:
    Gtk::VBox m_box;
    Gtk::TreeView m_header_view;
    Gtk::TextView m_body_view;
    Glib::RefPtr<Message> m_ref_message;
  };

}

#endif
