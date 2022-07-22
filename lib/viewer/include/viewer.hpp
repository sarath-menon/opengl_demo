#pragma once
#include "shader.hpp"
#include <GLFW/glfw3.h>

class Viewer {

private:
  GLFWwindow *handle_{};

  int width_{};
  int height_{};
  float aspect_ratio_{};

public:
  Viewer(const int width, const int height);

  void display(Shader &shader, double current_time);

  static void framebuffer_size_callback(GLFWwindow *handle, int width,
                                        int height);
  void processInput();

  void terminate();

  // getter functions

  auto getHandle() const { return handle_; }

  auto width() const { return width_; }

  auto height() const { return height_; }

  auto aspect_ratio() const { return aspect_ratio_; }
};