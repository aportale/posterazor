# PosteRazor for macOS by DiskyETH (https://github.com/Diskyeth) - 2025

## Dependencies

### Required
- **Qt 5.x or 6.x**
  ```bash
  brew install qt
  ```

### Optional
- **Poppler-Qt5** (for PDF input support)
  ```bash
  brew install poppler
  ```
- **FreeImage** (for additional image formats)
  ```bash
  brew install freeimage
  ```

## Building

1. Navigate to the source directory:
   ```bash
   cd src
   ```

2. Generate Makefile:
   ```bash
   qmake posterazor.pro
   ```

3. Build:
   ```bash
   make
   ```

4. Run:
   ```bash
   open PosteRazor.app
   ```

## Requirements

- macOS 10.15 (Catalina) or later
- Intel (x86_64) or Apple Silicon (arm64)

