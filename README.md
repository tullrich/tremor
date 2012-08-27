Tremor - Hobby Quake 3 Renderer
=========

Tremor is a hobby project that hopes to reimplement the rendering engine behind Quake 3 (you can find the source code [right here](https://github.com/id-Software/Quake-III-Arena) on github).

**work in progress, most features are incomplete**

Features
-----------
**Working**
* Currently supports very basic (non texture mapped) .md3 rendering.


**In Progress**
* .md3 Texture mapping

Building
----------

**Requisite Libraries**
* libSDL (tested with libsdl1.2)
* libjpeg (tested with libjpeg8)
* libGL
* libGLU

**Build System**  
[Scons](http://www.scons.org/) is the build system of choice. It aims to create a platform independent build processes. Tremor has been built successfully on GNU/Linux 3.2.0-23-generic x86_64.

To build, simply run `scons .` from the top level directory.
