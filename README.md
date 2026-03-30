# OpenCV HSV Color Detection and Contour Extraction (C++)

## Overview

This project demonstrates a complete HSV-based color segmentation pipeline using OpenCV and spdlog.

It performs:
- image loading
- BGR to HSV conversion
- real-time HSV threshold tuning with trackbars
- binary mask creation
- basic morphological denoising (erode and dilate)
- contour detection and drawing
- saving intermediate output images

This is useful for object segmentation, color detection, and vision preprocessing workflows.

## Features

- Real-time HSV tuning using trackbars
- HSV conversion (`BGR -> HSV`)
- Mask generation with `cv::inRange`
- Morphological noise removal (`erode`, `dilate`)
- Contour detection (`cv::findContours`)
- Logging via spdlog
- Output image export for HSV, mask, and contours

## Current Project Structure

```text
opencv/
|-- CMakeLists.txt
|-- main.cpp
|-- README.md
|-- imgs/
|   |-- test1.png
|   |-- hsv_test1.png        (generated)
|   |-- mask_test1.png       (generated)
|   \-- contour_test1.png    (generated)
|-- include/
|-- lib/
\-- build/
```

## Requirements

- C++ compiler (MSVC, MinGW, or Clang)
- CMake 3.11+
- OpenCV 4.x
- spdlog

## Dependencies

If using vcpkg:

```powershell
vcpkg install opencv spdlog
```

The project uses:
- `find_package(OpenCV REQUIRED)`
- `find_package(spdlog REQUIRED)`

## Build and Run (CMake)

From the project root:

```powershell
cmake -S . -B build
cmake --build build
```


## Processing Pipeline

1. Read input image from `imgs/test1.png`
2. Convert source image to HSV
3. Tune HSV threshold values using trackbars
4. Create mask using selected lower/upper HSV bounds
5. Apply erode and dilate to reduce noise
6. Detect external contours
7. Draw contours on a cloned original image
8. Save HSV, mask, and contour output images

## Trackbars

The app provides real-time controls for:
- `Low H` / `High H` (0 to 179)
- `Low S` / `High S` (0 to 255)
- `Low V` / `High V` (0 to 255)

## Output Windows

The following windows are displayed:
- Original Image
- HSV Image
- Mask
- Contours

## Saved Output Files

Generated in `imgs/`:
- `hsv_test1.png`
- `mask_test1.png`
- `contour_test1.png`

## Notes

- The current code uses absolute Windows paths. Update paths in `main.cpp` if your workspace location differs.
- For red color detection, two HSV ranges are often required (not currently implemented).
- Logging and image writing inside the main loop can affect performance.

## Possible Improvements

- Support multiple HSV ranges (for split hues such as red)
- Move input/output paths to command-line arguments
- Use bounding boxes or rotated rectangles for object annotation
- Save outputs on-demand instead of every frame
- Add optional webcam/video input mode

## License

This project is open source and available under the MIT License.