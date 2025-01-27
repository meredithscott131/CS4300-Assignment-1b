# The Rotating Square Illusion

This program is based on the [Rotating Square Illusion](https://mathworld.wolfram.com/RotatingSquareIllusion.html). This illusion is created by drawing several concentric rounded-corner squares, alternating in black and white colors, and then rotating the entire figure.

The rounded-corners of the squares are represented as a mesh in the RoundedCorner.h file. In Model.cpp, four RoundedCorners are created to make a complete rounded square. In View.cpp display(), these corners are duplicated to make multiple squares, transformed into their approproate orientation, and rotated to produce the illusion.

### Features
- Rounded-corner square mesh (RoundedCorner.h)
    - Made up of two rectangles and a quarter circle
- Duplication of squares (View.cpp display())
- Color assignment of squares (View.cpp display())
- Transformation and scaling of rounded-corner meshes (View.cpp display())
- Rotation of all meshes (View.cpp display())

To run the program after make use `./RotatingSquare`

<img src="Illusion.gif" width="400" height="400" />
