S3DR - Small 3D renderer
===============================

About
-----

S3DR is a small, openGL based, renderer library for the C++ programming language. 


Build requirements
------------------

* Main requirements:
    * C++11 standard compiler (GCC, Clang)
    * CMake - http://www.cmake.org/
    * GLM header only library - http://glm.g-truc.net/0.9.4/index.html
    * GLEW library - http://glew.sourceforge.net/
    * ImageMagick - www.imagemagick.org/
    * FreeType 2 - www.freetype.org/freetype2/

* Additionally required to compile a S3DR utility library:
    * Assimp library - http://assimp.sourceforge.net/  

* Additionally required to compile library tests and examples:
    * GLFW library - http://www.glfw.org/


Building
--------

In a local copy of the S3DR repository:

```bash
mkdir build
cd build
```

Run cmake:

```bash
cmake ..
```

Compile S3DR library:

```bash
make -j4
```

Main components of the S3DR library
-----------------------------------------

* Model
	* The model holds 3D graphics information (3D objects). 

* View
	* The view is responsible for the presentation of model data.
	* In general the view is used to change scene properties.

* Operator
	* The operator allow the end-user to interact with, or 'operate on' the model or view. 


Usage
-----

See tests folder for a basic examples.
