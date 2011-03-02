#ifndef __compose_compose_hpp
#define __compose_compose_hpp

#include <gtkmm/window.h>
#include <memory>
#include <sigc++/signal.h>

namespace Compose {

  class ComposeImpl;
  class Message;
  
  class Compose : public Gtk::Window {
  public:
    Compose();
    ~Compose();

    void set_message(Glib::RefPtr<Message>);

    sigc::signal<void, Glib::RefPtr<Message> > signal_send();
    sigc::signal<void> signal_cancel();

  private:
    std::auto_ptr<ComposeImpl> pimpl;
  };

}

#endif
