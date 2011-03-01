#ifndef __compose_compose_hpp
#define __compose_compose_hpp

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/paned.h>
#include <gtkmm/box.h>
#include <gtkmm/treeview.h>
#include <gtkmm/textview.h>
#include <gtkmm/window.h>
#include "message.hpp"
#include "header_view.hpp"

namespace Compose {
  
  class Compose : public Gtk::Window {
  public:
    Compose();

    void set_message(Glib::RefPtr<Message> message);

  private:
    Gtk::ScrolledWindow m_header_window;
    Gtk::ScrolledWindow m_body_window;
    Gtk::VPaned m_paned;
    Gtk::VBox m_box;
    HeaderView m_header_view;
    Gtk::TextView m_body_view;
    Glib::RefPtr<Message> m_ref_message;
  };

}

#endif
