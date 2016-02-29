# 2016 Revision on in2GPU tutorials chapter_2

## Table of contents

- [Visual Studio compatibility] (#visual-studio-compatibility)
- [OpenGL version] (#opengl-version)
- [Tools used] (#tools-used)
- [Acknowledgements] (#acknowledgements)

## Visual Studio compatibility

 This branch consists of fixes and updated version of the tutorials fully compatible with Visual Studio 2015;
 Originally tested on Visual Studio 2015 Enterprise Update #1. 
 TO DO: test backwards compatibility with VS 2013, VS 2015 Community.
 
### Structure:
 Modules: Basic Engine static library accompanied by a set of individual projects to test each newly added functionality in the Basic Engine.
 
```
Chapter_2/
├── Basic Engine/
│   ├── BMPHeaders.h
│   ├── ContextInfo.h
│   ├── DebugOutput.h
|   ├── Engine.h
|   ├── Engine.cpp
|   ├── Fragment_Shader.glsl
|   ├── FrameBufferInfo.cpp
|   ├── IGameObject.h
|   ├── IListener.h
|   ├── Init_GLEW.h
|   ├── Init_GLEW.cpp
|   ├── Init_GLUT.h
|   ├── Init_GLUT.cpp
|   ├── Model.h
|   ├── Model.cpp
|   ├── Model_Manager.h
|   ├── Model_Manager.cpp
|   ├── Quad.h
|   ├── Scene_Manager.h
|   ├── Scene_Manager.cpp
|   ├── Texture_Loader.h
|   ├── Texture_Loader.cpp
|   ├── Vertex_Shader.h
|   ├── VertexFormat.h
|   └── WindowInfo.h
├── Tests/
│   ├── Draw_Cube
|   ├── Draw_Cube_Index
|   ├── Draw_Cube_Texture
|   ├── Draw_Cube_Texture_SOIL
│   └── Draw_Sphere_Multitexturing
└── Shaders/
    ├── SimpleVert
    ├── SimpleFrag
    ├── MultitexturingVert
    └── MultitexturingFrag
```

## OpenGL version

The framework will contain upgrades from the previous version to OpenGL 4.5.
Changes include: removal of deprecated functionality (GL_QUADS, etc.), SOIL upgraded to OpenGL 4.5 core profile, shaders rewritten for the latest GLSL version.

## Tools used

```
External libraries/
├── Texture loading/
│   └── SOIL
├── Model loading/
│   └── Assimp
└── OpenGL functionality/
    ├── GLEW
    └── GLUT
Plugins and tools/
├── Visual Studio 2015 Enterprise Update 1
├── Nvidia NSight
└── QT 5.5
```

## Acknowledgements

- [Sergiu Craitoiu]()


