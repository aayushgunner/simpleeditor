#include <FL/Fl.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Window.H>
#include <FL/filename.H> // Required for fl_file_chooser
#include <FL/fl_ask.H>
#include <cstdlib>
#include <cstring>

// Global state
Fl_Text_Buffer *textbuf;
char filename[256] = "";
int doc_changed = 0;

class EditorWindow : public Fl_Window {
public:
  Fl_Text_Editor *editor;
  Fl_Menu_Bar *menu;

  EditorWindow(int W, int H, const char *L = 0) : Fl_Window(W, H, L) {
    menu = new Fl_Menu_Bar(0, 0, W, 25);
    menu->add("File/New", 0, new_cb, this);
    menu->add("File/Open", 0, open_cb, this);
    menu->add("File/Save", 0, save_cb, this);
    menu->add("File/Quit", 0, quit_cb, this);

    editor = new Fl_Text_Editor(0, 25, W, H - 25);
    editor->buffer(textbuf);
    this->resizable(editor);
  }

  // --- Callbacks ---

  static void new_cb(Fl_Widget *, void *v) {
    if (!check_save())
      return;
    textbuf->select(0, textbuf->length());
    textbuf->remove_selection();
    doc_changed = 0;
    strcpy(filename, ""); // clear filename
  }

  static void open_cb(Fl_Widget *, void *v) {
    if (!check_save())
      return;
    char *newfile = fl_file_chooser("Open File?", "*", filename);
    if (newfile)
      load_file(newfile);
  }

  static void save_cb(Fl_Widget *, void *) {
    if (filename[0] == '\0') {
      saveas_cb();
    } else {
      save_file(filename);
    }
  }

  static void saveas_cb() {
    char *newfile = fl_file_chooser("Save File As?", "*", filename);
    if (newfile)
      save_file(newfile);
  }

  static void quit_cb(Fl_Widget *, void *) {
    if (doc_changed && !check_save())
      return;
    exit(0);
  }

  // --- Helper Functions ---

  static int check_save() {
    if (!doc_changed)
      return 1;
    int r = fl_choice("The file has been modified.\nSave changes?", "Cancel",
                      "Save", "Discard");
    if (r == 1) {
      save_cb(nullptr, nullptr);
      return !doc_changed;
    }
    return (r == 2) ? 1 : 0;
  }

  static void load_file(const char *newfile) {
    int r = textbuf->loadfile(newfile);
    if (r) {
      fl_alert("Error reading from file '%s'", newfile);
    } else {
      strcpy(filename, newfile);
      doc_changed = 0;
    }
  }

  static void save_file(const char *newfile) {
    int r = textbuf->savefile(newfile);
    if (r) {
      fl_alert("Error writing to file '%s'", newfile);
    } else {
      strcpy(filename, newfile);
      doc_changed = 0;
    }
  }
};

// --- Modify Callback ---
void doc_changed_cb(int, int, int, int, const char *, void *) {
  doc_changed = 1;
}

// --- Main Function ---
int main(int argc, char **argv) {
  textbuf = new Fl_Text_Buffer();
  textbuf->add_modify_callback(doc_changed_cb, nullptr);

  EditorWindow win(640, 480, "FLTK Editor");
  win.show(argc, argv);

  if (argc > 1)
    EditorWindow::load_file(argv[1]);

  return Fl::run();
}
