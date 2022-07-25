#pragma once

#include <glad/glad.h>
//
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shader.hpp"

class Camera {
public:
  // Stores the main vectors of the camera
  glm::vec3 position_;
  glm::vec3 orientation_ = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

  // Prevents the camera from jumping around when first clicking left click
  bool firstClick = true;

  // Stores the width and height of the window
  int width{};
  int height{};

  // Adjust the speed of the camera and it's sensitivity when looking around
  float speed = 0.1f;
  float sensitivity = 100.0f;

  // Camera constructor to set up initial values
  Camera(const int width, const int height, const glm::vec3 position);

  // Updates and exports the camera matrix to the Vertex Shader
  void Matrix(const float fov_degrees, const float near_plane,
              const float far_plane, const Shader &shader,
              const char *uniform) const;
  // Handles camera inputs
  void Inputs(GLFWwindow *window);
};