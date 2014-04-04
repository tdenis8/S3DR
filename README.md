S3DR - Small 3D renderer
===============================

About
-----

S3DR is a small 3D, openGL based, renderer for the C++ programming language. 


Build requirements
------------------

* Main requirements:
  * C++11 compiler (GCC, Clang)
  * GLM header only library - http://glm.g-truc.net/0.9.4/index.html
  * GLEW library - http://glew.sourceforge.net/
  * premake4 - http://industriousone.com/premake

* Required to compile a Fenix3D utility library:
  * Assimp library - http://assimp.sourceforge.net/

* Required to compile library tests and examples:
  * GLFW library - http://www.glfw.org/


Building
--------

Clone a copy of the main S3DR git repo:

```bash
git clone git@github.com:tdenis8/S3DR.git
```

Enter the S3DR directory:

```bash
cd S3DR
```

Generate makefiles:

```bash
premake4 gmake
```

Compile S3DR library(S3DR/lib/libs3dr.a):

```bash
make config=release verbose=true -j 4
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

TODO
