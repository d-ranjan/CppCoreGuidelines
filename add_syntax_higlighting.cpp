#include <fstream>
#include <iostream>
#include <string>

int main() {
  const std::string source_file{"CppCoreGuidelines.md"};
  const std::string dest_file{"CppCoreGuidelinesWithHighlighting.md"};

  std::ifstream in_stream(source_file);
  std::ofstream out_stream(dest_file);

  if (!in_stream.is_open()) {
    std::cout << "failed to open " << source_file << '\n';
    return EXIT_FAILURE;
  }
  std::cout << "opened " << source_file << " successfully\n";

  if (!out_stream.is_open()) {
    std::cout << "failed to open " << dest_file << '\n';
    return EXIT_FAILURE;
  }
  std::cout << "opened " << dest_file << " successfully\n";

  bool is_codeblock_started{false};
  std::string prev_line;
  for (std::string line; std::getline(in_stream, line);) {
    bool is_codeblock = line.starts_with("    ");
    if (is_codeblock) {
      if (!is_codeblock_started) {
        if (line.empty()) {
          out_stream << "```cpp\n";
        } else {
          out_stream << "```cpp\n" << line.replace(0, 4, "") << '\n';
        }
        is_codeblock_started = true;
      } else {
        out_stream << line.replace(0, 4, "") << '\n';
      }
    } else {
      if (is_codeblock_started && !line.empty()) {
        out_stream << "```\n" << line << '\n';
        is_codeblock_started = false;
      } else {
        out_stream << line << '\n';
      }
    }
  }
  std::cout << "wrote highlighted version to " << dest_file << " successfully\n";
}
