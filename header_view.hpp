#ifndef __compose_header_view_hpp
#define __compose_header_view_hpp

#include <memory>
#include <gtkmm/treeview.h>

namespace Compose {

  class HeaderViewImpl;
  class Message;

  class HeaderView : public Gtk::TreeView {
  public:
    HeaderView();
    ~HeaderView();
    
    void set_message(Glib::RefPtr<Message>);

  private:
    std::auto_ptr<HeaderViewImpl> pimpl;
  };

}

#endif
