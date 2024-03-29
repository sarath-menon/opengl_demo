#include "EBO.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "camera.hpp"
#include "cube.hpp"
#include "shader.hpp"
#include "stb_image.h"
#include "timer.hpp"
#include "triangle.hpp"
#include "viewer.hpp"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

int main() {

  constexpr float width = 600;
  constexpr float height = 600;

  constexpr float cam_pos[3] = {0.0f, 0.0f, 5.0f};
  const gl::V3 cube_pos = gl::V3(1.0, -2.0, -1.0);
  const glm::vec4 obj_colour = glm::vec4(0.8f, 0.3f, 0.02f, 1.0f);

  Viewer viewer(width, height, "Cube with vertices drawn using indices");
  Shader obj_shader("shaders/3d_constcolour_vshader.glsl",
                    "shaders/3d_constcolour_fshader.glsl");
  Camera camera(width, height, glm::vec3(glm::make_vec3(cam_pos)));
  Cube cube(cube_pos, 1.0);

  // to hold id's of uniform variables
  GLuint model_loc;

  cube.set_scale(0.5f);

  // vertex array object to prganize vertex buffers
  VAO va;
  // vertex buffer to be sent to vertex shader
  VBO vb[2];
  vb[0].set_vertices(cube.vertices());

  // Generates Element Buffer Object and links it to indices
  EBO EBO1(cube.indices());

  // Transformation matrices
  gl::A3 model_m = gl::A3::Identity();
  // get locations of uniforms in the shader program
  model_loc = glGetUniformLocation(obj_shader.getHandle(), "model");

  cube.set_global_position(gl::V3(1.0f, 1.0f, 1.0f));

  // Load the compiled shaders to the GPU
  obj_shader.Activate();

  // set object colour
  glUniform4f(glGetUniformLocation(obj_shader.getHandle(), "obj_colour"),
              obj_colour.x, obj_colour.y, obj_colour.z, obj_colour.w);

  // Link VBO to  VAO
  va.set_vertex_attrb_ptrs(vb[0], 0, GL_FLOAT);

  //  Render loop: show window till close button is pressed
  while (!glfwWindowShouldClose(viewer.getHandle())) {
    // Inputs
    viewer.processInput();
    // clear display
    viewer.clear_display();

    // Camera ////////////////////////////////
    // camera
    // Handles camera inputs
    camera.Inputs(viewer.getHandle());

    // Update the camera position according to mouse interaction
    camera.updateMatrix();

    // Draw cube ////////////////////////////////

    cube.global_rotate_y(M_PI / 100.0f);

    // create model matrix
    model_m = cube.global_pose();

    // copy matrix data to corresponding uniform variables
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, model_m.data());

    // send data in vertex buffer to the obj_shader and start drawing
    glDrawElements(GL_TRIANGLES, cube.indices().size(), GL_UNSIGNED_INT, 0);

    //////////////////////////////////////////////////////////
    // Export the camMatrix to the Vertex Shader of the pyramid
    camera.Matrix(obj_shader, "cam_view");
    viewer.start_display();
  }
}
