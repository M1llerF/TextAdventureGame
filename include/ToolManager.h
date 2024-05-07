#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H
#include <memory>
#include <vector>

#include "CaesarCipherWheelTool.h"
#include "FrequencyAnalysisTool.h"
#include "MorseCodeDecrypterTool.h"
#include "Tool.h"

class ToolManager {
 private:
  std::vector<std::shared_ptr<Tool>> tools;

 public:
  ToolManager() { initializeTools(); }

  void initializeTools() {
    tools.push_back(std::make_shared<MorseCodeDecrypterTool>());
    tools.push_back(std::make_shared<CaesarCipherWheelTool>());
    tools.push_back(std::make_shared<FrequencyAnalysisTool>());
  }

  const std::vector<std::shared_ptr<Tool>>& getTools() const { return tools; }
};
#endif  // TOOLMANAGER_H
