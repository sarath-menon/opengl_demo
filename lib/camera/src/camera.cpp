#include "camera.hpp"

Camera::Camera(const int width, const int height, const glm::vec3 position) {
  Camera::width = width;
  Camera::height = height;
  position_ = position;
}

void Camera::updateMatrix() {
  // Initializes matrices since otherwise they will be the null matrix
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

  // Makes camera look in the right direction from the right position
  view = glm::lookAt(position_, position_ + orientation_, Up);
  // Adds perspective to the scene
  projection = glm::perspective(glm::radians(fov_degrees_),
                                (float)width / height, near_plane_, far_plane_);

  // Sets new camera matrix
  cam_mat = projection * view;
}

void Camera::Matrix(Shader &shader, const char *uniform) {
  // Exports camera matrix
  glUniformMatrix4fv(glGetUniformLocation(shader.getHandle(), uniform), 1,
                     GL_FALSE, glm::value_ptr(cam_mat));
}

void Camera::Inputs(GLFWwindow *window) {
  // Handles key inputs
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    position_ += speed * orientation_;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    position_ += speed * -glm::normalize(glm::cross(orientation_, Up));
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    position_ += speed * -orientation_;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    position_ += speed * glm::normalize(glm::cross(orientation_, Up));
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    position_ += speed * Up;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    position_ += speed * -Up;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    speed = 0.4f;
  } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
    speed = 0.1f;
  }

  // Handles mouse inputs
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    // Hides mouse cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // Prevents camera from jumping on the first click
    if (firstClick) {
      glfwSetCursorPos(window, (width / 2), (height / 2));
      firstClick = false;
    }

    // Stores the coordinates of the cursor
    double mouseX;
    double mouseY;
    // Fetches the coordinates of the cursor
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // Normalizes and shifts the coordinates of the cursor such that they begin
    // in the middle of the screen and then "transforms" them into degrees
    float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
    float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

    // Calculates upcoming vertical change in the orientation_
    glm::vec3 neworientation_ =
        glm::rotate(orientation_, glm::radians(-rotX),
                    glm::normalize(glm::cross(orientation_, Up)));

    // Decides whether or not the next vertical orientation_ is legal or not
    if (abs(glm::angle(neworientation_, Up) - glm::radians(90.0f)) <=
        glm::radians(85.0f)) {
      orientation_ = neworientation_;
    }

    // Rotates the orientation_ left and right
    orientation_ = glm::rotate(orientation_, glm::radians(-rotY), Up);

    // Sets mouse cursor to the middle of the screen so that it doesn't end up
    // roaming around
    glfwSetCursorPos(window, (width / 2), (height / 2));
  } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==
             GLFW_RELEASE) {
    // Unhides cursor since camera is not looking around anymore
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    // Makes sure the next time the camera looks around it doesn't jump
    firstClick = true;
  }
}