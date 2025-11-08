# Image Compression Using Truncated SVD
### Project Overview & How to Run

---

##  Overview
This project performs **image compression** using the **Truncated Singular Value Decomposition (SVD)** technique.

- A grayscale image (PGM format) is converted into a matrix.  
- Only the top `k` singular values are used to reconstruct the image.  
- This reduces file size while preserving most visual details.  
- Implemented completely in **C**, without using any external libraries.

---

##  How to Compile & Run

From inside the `codes/` folder, run the following commands:

```bash
# Compile the program
gcc c_main/main.c c_libs/matrix_ops.c c_libs/pgm_io.c c_libs/svd.c -lm -o svd_compress

# Run the program
./svd_compress <input.pgm> <output.pgm> <k>
