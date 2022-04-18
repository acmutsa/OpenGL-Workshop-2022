# OpenGL Workshop
This repository is dedicated to holding all the content in UTSA ACM's Spring 2022 Introduction to OpenGL Workshop.

## Setup

### Prerequisites

- [GLFW](https://www.glfw.org/download.html) for window-handling, download the 64 bit binaries
- [Glad](https://glad.dav1d.de/) for loading OpenGL functions (this tutorial uses 4.5 Core)
- [GLM](https://github.com/g-truc/glm) for mathematics


### Visual Studio Community

First, ensure that you have a computer that is compatible with modern OpenGL (which, should be most made within the last 5 - 7 years). Make sure you place your dependencies in an easy to navigate folder

Download the prerequisites listed above, then in VS Community, make a new project. Select "Windows Desktop Wizard" and name your project as you wish. When prompted, make sure that "Empty Project" is checked and that your application type is "Console Application"

Before adding in your libraries, right click on **Source Files**, then under "New" click "Add New Item". Create a .cpp file.

To configure project properties, go to **Project > {Project Name} Properties**. Under **C/C++ > General** add your dependencies include directories to *Additional Include Directories*. This will likely be ``placedDirectory\glad\include``, ``placedDirectory\glfw.bin.WIN64\include``, ``placedDirectory\glm``.

Then under **Linker > General**, in *Additional Library Directories* add the lib directory from your glfw folder (this will be something like: ``glfw.bin.WIN64\lib``). 

Thereafter, in **Linker > Input** under *Additional Dependecies* add the following entries: ``glu32.lib``, ``opengl32.lib``, ``glfw3.lib``. 

You will also need to add the ``glad.c`` file from your Glad installation onto your project. You can do this by *Add an existing item* option, after right click Source Files, then finding the relevant ``glad.c`` file. 

Finally, try running some of the demos! Experiment as desired!
 
### Linux

TBD

