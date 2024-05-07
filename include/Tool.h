/**
 * @file: Tool.h
 * @author: Miller Fourie
 * @date: 2024-03-05
 */
#ifndef TOOL_H
#define TOOL_H
#include <string>

class Tool {
 protected:
  std::string toolName;
  std::string toolDescription;

 public:
  // Virtual destructor to ensure proper cleanup of derived classes
  virtual ~Tool() {}

  // Pure virtual function makes Tool an abstract class
  virtual std::string useTool(const std::string& decryptTest) = 0;

  // Inline member functions to return tool name and description
  std::string getToolName() const { return toolName; }
  std::string getToolDescription() const { return toolDescription; }
};

#endif  // TOOL_H
