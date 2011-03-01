#ifndef __compose_message_hpp
#define __compose_message_hpp

#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/liststore.h>
#include <gtkmm/textbuffer.h>

namespace Compose {

  class HeaderModelColumns : public Gtk::TreeModelColumnRecord {
  public:
    HeaderModelColumns();

    Gtk::TreeModelColumn<Glib::ustring> m_name;
    Gtk::TreeModelColumn<Glib::ustring> m_value;
    Gtk::TreeModelColumn<bool> m_shown;
  };

  const HeaderModelColumns &header_model();

  struct Message : public Glib::Object {
    Message();

    Glib::RefPtr<Gtk::TextBuffer> m_ref_body_buffer;
    Glib::RefPtr<Gtk::ListStore> m_ref_headers;

    void connect_header_edited(Glib::SignalProxy2<void, const Glib::ustring &, const Glib::ustring &>);
  private:
    void on_header_edited(const Glib::ustring &, const Glib::ustring &);
  };
}

#endif
