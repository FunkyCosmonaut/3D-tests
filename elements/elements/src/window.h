#define GLFW_INCLUDE_NONE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "input.h"
#include "render.h"

//Heads up, GLFW_INCLUDE_NONE because glfw defs conflict with glads
//GLES 3.0 header is included in glad.
//cglm is installed :)
