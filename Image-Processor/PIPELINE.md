## Pipeline for Image Processing

This document outlines the pipeline for processing images in the Image Processor project. The pipeline consists of several stages, each responsible for a specific aspect of image processing.
### Input Image Loader (BMP format – simplest to parse manually):
- Load image from BMP file
- Check if the image is grayscale
- If not, convert to grayscale

### Resize to 32x32 (by padding or cropping)
- Resize the image to 32x32 pixels
- If the image is smaller, pad it with zeros (white pixels)
- If the image is larger, crop it to fit
- Ensure the aspect ratio is maintained if necessary.

### Enhance Image (simple contrast and brightness scaling)
- Apply contrast enhancement by scaling pixel values
- Apply brightness adjustment by adding a constant value to pixel intensities
- Ensure pixel values remain within valid range (0-255)
- This can be done using simple linear transformations.
- 
### Binarization (Otsu's method)
- Apply Otsu's method to determine an optimal threshold
- Convert the image to binary (black and white) based on the threshold

### Save as .h file (C array) and as a .BMP file to view the result
- Convert the processed image into a C array format
- Save the C array to a .h file for use in C programs