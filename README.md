## 📝 Memo-Pad++

A simple text editor built with C++ and SDL2, featuring real-time rendering of the cursor and responsive buttons.

### 🔧 Features
- ✅ Real-time cursor rendering based on window size
- ✅ Text input with line breaks (Enter)
- ✅ Backspace to remove last character or line
- ✅ Ctrl+N: Clear all text
- ✅ Ctrl+C: Copy all text to clipboard
- ✅ Ctrl+V: Paste clipboard content
- ✅ Ctrl+Q: Exit application

### 🔍 How It Works
The app uses SDL2 for rendering and TTF for font rendering. Text is stored in a vector of strings, with each line rendered independently.

### 🚀 Compilation & Usage

1. **Prerequisites**
   - Install SDL2 and SDL2_ttf development libraries (Ubuntu) and CMake:
     ```bash
     sudo apt update && sudo apt install libsdl2-dev libsdl2-ttf-dev cmake
     ```

2. **Compile**
   Run the Makefile to build the application:
   ```bash
   cmake .
   make
   ```

3. **Run**
   Execute the binary:
   ```bash
   ./bin/memo-pad-cpp
   ```

### 📝 Tips
- Press `Enter` to insert a new line.
- Use `Ctrl+C` and `Ctrl+V` to copy/paste text.
- The app automatically align buttons based on window dimensions.
- Text is rendered with smooth cursor highlighting.

> ⚠️ This is a lightweight, educational project. For production use, consider additional features like file I/O or saving/loading.

