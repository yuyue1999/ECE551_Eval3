#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
class page {
  unsigned long pagenumber;
  char state;
  std::string pagetxt;
  std::vector<std::pair<std::string, std::string> > Trans;
  std::string dir;
  size_t index;
  std::vector<std::pair<std::string, std::string> > Vars;
  //std::vector<std::pair<std::string, std::string> > conditions;
  //std::vector<std::string> content;
  std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string> > > NewTransfer;
    std::vector<std::string> content;
 public:
  page() : pagetxt(NULL) {}
  page(unsigned long pg,
       char sta,
       std::string txt,
       std::vector<std::pair<std::string, std::string> > tTrans,
       std::string tdir,
       size_t i) :
      pagenumber(pg), state(sta), pagetxt(txt), Trans(tTrans), dir(tdir), index(i) {
    pageRead();
  }

  page(unsigned long pg,
       char sta,
       std::string txt,
       std::vector<std::pair<std::string, std::string> > tTrans,
       std::string tdir,
       size_t i,
       std::vector<std::pair<std::string, std::string> > inputV,
       std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string> > > inputC) :
      pagenumber(pg),
      state(sta),
      pagetxt(txt),
      Trans(tTrans),
      dir(tdir),
      index(i),
      Vars(inputV),
      NewTransfer(inputC) {
    pageRead();  //change here!!!
  }

  size_t getIndex() { return index; }
  char getState() { return state; }
  unsigned long getPagenum() { return pagenumber; }
  std::vector<std::pair<std::string, std::string> > & getTrans() { return Trans; }
  std::vector<std::pair<std::string, std::string> > & getVars() { return Vars; }
    std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string> > > & getNewTransfer() { return NewTransfer; }
  void pageRead() {
    std::string temp = dir;
    temp.append("/");
    temp.append(pagetxt);
    std::string s1;
    char * cstr = new char[temp.length() + 1];
    std::strcpy(cstr, temp.c_str());
    std::ifstream f(cstr);
    if (f.fail()) {
      std::cerr << "Can't open file or the file does not exist!" << std::endl;
      exit(EXIT_FAILURE);
    }
    while (!f.eof()) {
      std::getline(f, s1);
      content.push_back(s1);
    }
    f.close();
    delete[] cstr;
  }
  void pageprint(bool printPageNum) {
    if (printPageNum) {
      std::cout << "Page " << pagenumber << std::endl;
      std::cout << "==========" << std::endl;
    }

    //  pageRead();
    for (size_t i = 0; i < content.size(); i++) {
      std::cout << content[i] << std::endl;
    }
    //    std::cout << std::endl;
    if (state == 'N') {
      std::cout << "What would you like to do?";
      std::cout << std::endl;
      std::cout << std::endl;
      for (size_t i = 0; i < Trans.size(); i++) {
        std::cout << " " << i + 1 << ". " << Trans[i].second << std::endl;
      }
    }
    else if (state == 'L') {
      std::cout << "Sorry, you have lost. Better luck next time!";
      std::cout << std::endl;
    }
    else if (state == 'W') {
      std::cout << "Congratulations! You have won. Hooray!";
      std::cout << std::endl;
    }
  }
  void pageprintcontent() {
    for (size_t i = 0; i < content.size(); i++) {
      std::cout << content[i] << std::endl;
    }
  }
};
/* page_h */
