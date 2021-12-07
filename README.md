# Software Rasterizer

This project is a software rasterizer that is capable of displaying 3D models (.OBJ files). Traditional triangle rasterization is handled through the hardware of a GPU, so the goal of this project was to be able to load, process, and display a 3D model through software alone.

## Cloning

Since this project's dependencies are managed through Git submodules, the repository should be cloned with the ``--recursive`` flag:

```git clone --recursive https://github.com/cs128-2021c/final-project-3d-renderers.git```

This flag will recursively clone the libraries to their respective folders, where they will later be built as well.

## Building

The CMake build system is used to build this project along with its dependencies. Assuming that CMake has been installed, the following should configure the build:

```
# starting in the parent directory
mkdir build
cd build
cmake ..
```

 Alternatively, Visual Studio Code also has a CMakeTools extension that automatically configures the build for you. Once the files have been generated, you can use the Makefiles to build the project.

## Executing

The application takes in a single argument which should contain the filepath of the 3D model to be rendered:

```
# in the build directory
./rasterizer "[filepath]"
```

If no argument is provided, the application will instead prompt the user to re-run the executable with an additional argument.

When the application is running, the following options should be available:
- ``WASD`` to move forward/backward and sideways
- ``EQ`` to move up or down
- ``IJKL`` to rotate up/down or side-to-side
- ``[]`` to rotate the light around the object
- ``+-`` to increase or decrease movement speed
- ``X`` to close out of the application

## Testing

The CMake should've also configured the Makefile to build to the test suite. Catch2 is used as the testing framework, and can be run by simply calling the executable:

```
./tests
```

## Credit

This project was created by Jeffrey Liu, Paymon Sadat, and Chase Hari as part of UIUC's CS128 final project.
