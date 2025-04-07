# Terminal-Based-Image-Processing

This project involves the development of a command-line based image processing application in C++. The program is designed to manipulate images in the Portable Pixmap (PPM) format through a series of common transformations. It is implemented as a terminal application that takes input and output file paths, along with processing options, directly from command-line arguments. The primary objective is to provide a practical application of foundational programming concepts such as file handling, vector manipulation, control structures, and modular function design within the context of digital image processing.

Functionality
The program supports a suite of image processing operations, each of which can be activated through specific command-line flags:

Grayscale Conversion (-g): Converts a color image to grayscale by setting each pixel's RGB values to the average of the three components.
Color Inversion (-i): Inverts the image colors by subtracting each RGB value from 255.
Contrast Adjustment (-x): Enhances image contrast using the formula
NewColor = (OriginalColor - 128) * 1.2 + 128,
with results clamped between 0 and 255.
Blurring (-b): Applies a box blur filter by averaging each pixel’s RGB values with its eight immediate neighbors, excluding the border pixels.
Mirroring (-m): Horizontally flips the image by reversing each row of pixels.
Compression (-c): Reduces image resolution by discarding every other row and column, implementing a lossy compression algorithm.
All processing options can be combined in any order to perform compound transformations. The sequence of applied effects corresponds to the order in which the options are specified in the command line.

Debug Mode
An optional debug mode (-debug) is available to print pixel RGB values before and after each transformation. This mode assists in visualizing intermediate states and verifying the correctness of the processing logic, particularly useful for small test images.

Technical Implementation
The image data is stored using a two-dimensional std::vector of custom RGB structures, preserving spatial layout.
All file I/O operations are performed on .ppm images, utilizing external helper functions provided via the ppmio.h and ppmio.cpp files.
Modular functions handle each transformation separately, promoting code clarity and maintainability.
Robust error checking ensures graceful handling of incorrect usage, missing arguments, unreadable files, and unrecognized options.

