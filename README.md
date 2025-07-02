# FLTK Text Editor

A simple, lightweight text editor built with FLTK (Fast Light Toolkit) in C++. This editor provides basic text editing functionality with a clean, minimalist interface.

## Prerequisites

Before building the editor, you need to have FLTK installed on your system.

#### Building FLTK from Source

```bash
wget https://www.fltk.org/pub/fltk/1.3.8/fltk-1.3.8-source.tar.gz
tar xzf fltk-1.3.8-source.tar.gz
cd fltk-1.3.8
./configure
make
sudo make install
```

## Building the Editor

### Clone the Repository

```bash
git clone https://github.com/aayushgunner/simpleeditor.git
cd simpleeditor
```

### Compile

```bash
g++ main.cpp -o editor `fltk-config --cxxflags --ldflags`
```

## Usage

### Running the Editor

```bash
./editor
```

### Opening a File at Startup

```bash
./editor filename.txt
```

### Keyboard Shortcuts

- **Ctrl+N**: New file (via File menu)
- **Ctrl+O**: Open file (via File menu)
- **Ctrl+S**: Save file (via File menu)
- **Ctrl+Q**: Quit (via File menu)

_Note: Keyboard shortcuts work through the File menu_

### File Operations

- **New**: Creates a new empty document
- **Open**: Opens an existing text file using a file dialog
- **Save**: Saves the current document
  - If the file hasn't been saved before, it will prompt for a filename
  - If the file already has a name, it saves directly
- **Quit**: Exits the application
  - Prompts to save if there are unsaved changes

## Acknowledgments

- [FLTK Team](https://www.fltk.org/) for the excellent GUI toolkit
- FLTK community for documentation and examples

