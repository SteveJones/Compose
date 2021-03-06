#ifndef __compose_compose_impl_hpp
#define __compose_compose_impl_hpp

#include <glibmm/refptr.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/paned.h>
#include <gtkmm/box.h>
#include <gtkmm/treeview.h>
#include <gtkmm/textview.h>
#include "header_view.hpp"

namespace Gtk {
  class Window;
}

namespace Compose {

  class Message;

  class ComposeImpl {
  public:
    ComposeImpl(Gtk::Window *);

    void set_message(Glib::RefPtr<Message>);

    sigc::signal<void, Glib::RefPtr<Message> > signal_send();
    sigc::signal<void> signal_cancel();

  protected:
    virtual void on_send_clicked();
    virtual void on_cancel_clicked();

  private:
    Gtk::ScrolledWindow m_header_window;
    Gtk::ScrolledWindow m_body_window;
    Gtk::VPaned m_paned;
    Gtk::VBox m_box;
    HeaderView m_header_view;
    Gtk::TextView m_body_view;
    Glib::RefPtr<Message> m_ref_message;
    Gtk::Window *m_parent;
    Gtk::Button m_send_button;
    Gtk::Button m_cancel_button;
    Gtk::HBox m_button_box;

    sigc::signal<void, Glib::RefPtr<Message> > m_signal_send;
    sigc::signal<void> m_signal_cancel;
  };

}

#endif
