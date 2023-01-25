#include "story.h"
int main(int argc, char ** argv) {
    /*
  if (argc == 1 || argc > 2) {
    std::cerr << "invalid input!" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string targetStory = argv[1];
  targetStory.append("/story.txt");
  std::string s1;
  std::vector<std::string> store;
  char * cstr = new char[targetStory.length() + 1];
  std::strcpy(cstr, targetStory.c_str());
  std::ifstream f(cstr);

  if (f.fail()) {
    std::cerr << "Can't open file or the file does not exist!" << std::endl;
    exit(EXIT_FAILURE);
  }
  while (!f.eof()) {
    std::getline(f, s1);
    if (s1 == "") {
      continue;
    }
    store.push_back(s1);
  }

  story s(store, argv[1]);
  s.parseForVariable();
  if (!s.checkValidRefer()) {
    std::cerr << "Invalid 3a! Not every page that is referenced by a choice is valid"
              << std::endl;
    exit(EXIT_FAILURE);
  }
  if (!s.checkPageRefered()) {
    std::cerr << "Invalid!3b! Not Every page (except page 0) is referenced by at least "
                 "one *other* pages choices. "
              << std::endl;
    exit(EXIT_FAILURE);
  }
  if (!s.checkWinOrLose()) {
    std::cerr << "Invalid!3c! Not At least one page must be a WIN page and at least one "
                 "page must be a LOSE page. "
              << std::endl;
    exit(EXIT_FAILURE);
  }
  s.UserReadingForVar();
  store.clear();
  f.close();
  delete[] cstr;*/
    std::string userInput("1 2");
    
    int userChoice = std::atoi(userInput.c_str());
    std::cout<<userChoice;
  return EXIT_SUCCESS;
}
