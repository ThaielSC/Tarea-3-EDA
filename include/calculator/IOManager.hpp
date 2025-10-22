#include <istream>

class IOManager {
private:
  std::istream &input;
  std::ostream &output;
  std::string buffer;
  const std::string PROMPT = ">> ";

public:
  IOManager(std::istream &input, std::ostream &output);

  void read();

  void write(std::string msg);

  std::string getBuffer();
};
