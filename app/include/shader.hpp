#pragma once
#include "include_glad.h"

class Shader {
public:
  Shader();

  auto &get_program() { return shaderProgram_; }

  // Activates the Shader Program
  void Activate();

  // Deletes the Shader Program
  void Delete();

private:
  // Create Shader Program Object and get its reference
  GLuint shaderProgram_{};

  void create_program_shader();

  std::string readShaderSource(const char *filePath);

  // Checks if the different Shaders have compiled properly
  void compileErrors(unsigned int shader, const char *type);
};