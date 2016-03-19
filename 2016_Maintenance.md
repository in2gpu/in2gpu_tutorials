# 2016 Revision on in2GPU tutorials chapter_2

## Table of contents

- [Visual Studio compatibility] (#visual-studio-compatibility)
- [OpenGL version] (#opengl-version)
- [Tools used] (#tools-used)
- [Acknowledgements] (#acknowledgements)

## Visual Studio compatibility

 This branch consists of fixes and updates of the tutorial series thus far in order to make the series fully compatible with OpenGL 4.5 core;
 Originally tested on Visual Studio 2015 Enterprise Update 1 and Visual Studio 2015 Community.



## OpenGL version

The framework will contain upgrades from the previous version to OpenGL 4.5 core;
Changes include: removal of deprecated functionality (GL_QUADS, etc.), SOIL upgraded to SOIL2, C++ Chrono will make use of steady_clock throughout the series.

## Tools used

```
External libraries/
├── Texture loading/
│   └── SOIL2
├── Model loading/
│   └── Assimp
└── OpenGL functionality/
    ├── GLEW
    └── FreeGLUT
Plugins and tools/
├── Visual Studio 2015 Enterprise Update 1
├── Nvidia NSight
└── QT 5.5
```

## Acknowledgements

- [Sergiu Craitoiu] (https://twitter.com/SergiuCraitoiu)
- [Vlad Badoiu]
- [Michael Pohoreski]
- [Ana Mihut] (https://twitter.com/Vannaheim)
