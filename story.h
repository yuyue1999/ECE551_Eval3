#include <queue>

#include "page.h"
class story {
 private:
  std::vector<std::string> wholeStory;
  std::vector<page *> store;
  std::string directory;
  std::vector<std::vector<std::pair<int, size_t> > > result;
  std::vector<std::pair<std::string, std::string> > currentVar;

 public:
  story() {}
  story(std::vector<std::string> input, std::string tdir) :
      wholeStory(input), directory(tdir) {}
  std::vector<page *> & getStore() { return store; }
  //consider for the corner cases for step1
  //A page declaration (num@filename) for a given page must appear before anything else related to that page (choices, now, or other things in Step 4).
  //Page declarations must appear in order.  That is, the declaration for page 0 (0@N:...) must be first, then the next page declaration (1@N:...)
  //Win and Lose pages MUST NOT have any choices.
  //Choices may appear at any time after the page declaration.
  void check() {
    std::string str3(":");
    std::string st2("@");
    for (size_t i = 0; i < wholeStory.size(); i++) {
      size_t temp = wholeStory[i].find(st2);
      if (temp < wholeStory[i].length()) {
        char page_state = wholeStory[i].at(temp + 1);
        /*if (page_state != 'L' || page_state != 'W' || page_state != 'N') {
          std::cerr << "invalid format" << std::endl;
          exit(EXIT_FAILURE);
        }*/
        char * cstr = new char[wholeStory[i].length() + 1];
        std::strcpy(cstr, wholeStory[i].c_str());
        unsigned long pagenumber = std::strtoul(cstr, NULL, 0);
        delete[] cstr;
        for (size_t j = 0; j < i; j++) {
          char * cstr1 = new char[wholeStory[j].length() + 1];
          std::strcpy(cstr1, wholeStory[j].c_str());
          unsigned long findchoice = std::strtoul(cstr1, NULL, 0);
          delete[] cstr1;
          if (findchoice == pagenumber) {
            std::cerr << "invalid format" << std::endl;
            exit(EXIT_FAILURE);
          }
        }
        if (page_state == 'W' || page_state == 'L') {
          for (size_t k = i + 1; k < wholeStory.size(); k++) {
            char * cstr1 = new char[wholeStory[k].length() + 1];
            std::strcpy(cstr1, wholeStory[k].c_str());
            unsigned long findchoice1 = std::strtoul(cstr1, NULL, 0);
            delete[] cstr1;
            if (findchoice1 == pagenumber) {
              std::cerr << "invalid format" << std::endl;
              exit(EXIT_FAILURE);
            }
          }
        }
      }
      else {
        size_t find1 = wholeStory[i].find(str3);
        if (find1 > wholeStory[i].length()) {
          std::cerr << "invalid format" << std::endl;
          exit(EXIT_FAILURE);
        }
        size_t find2 = wholeStory[i].find(str3, find1 + 1);
        if (find2 > wholeStory[i].length()) {
          std::cerr << "invalid format" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
    }
    /*
    for (size_t i = 0; i < wholeStory.size(); i++) {
      size_t findAt = wholeStory[i].find(st2);
      size_t findColon = wholeStory[i].find(str3);
      if (findAt < wholeStory[i].length()) {
        std::string number = wholeStory[i].substr(0, findAt - 1);
        if (!isNumber(number)) {
          std::cerr << "invalid format" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      else if (findColon < wholeStory[i].length()) {
        std::string number = wholeStory[i].substr(0, findColon - 1);
        if (!isNumber(number)) {
          std::cerr << "invalid format" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      }*/
    for (size_t i = 0; i < store.size(); i++) {
      if (store[i]->getPagenum() != i) {
        std::cerr << "invalid format" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }
  //parse the file story.txt, build *pages and store them in vector;
  void parse() {
    std::string st2("@");
    for (size_t i = 0; i < wholeStory.size(); i++) {
      size_t temp = wholeStory[i].find(st2);
      if (temp < wholeStory[i].length()) {
        char page_state = wholeStory[i].at(temp + 1);
        std::string pagetxt = wholeStory[i].substr(temp + 3);
        //std::string::size_type sz = 0;
        char * cstr = new char[wholeStory[i].length() + 1];
        std::strcpy(cstr, wholeStory[i].c_str());
        //std::string::size_type sz = 0;
        unsigned long pagenumber = std::strtoul(cstr, NULL, 0);
        delete[] cstr;
        std::vector<std::pair<std::string, std::string> > Transfer;
        if (page_state == 'N') {
          for (size_t j = 0; j < wholeStory.size(); j++) {
            size_t temp2 = wholeStory[j].find(st2);
            if (temp2 > wholeStory[j].length()) {
              //std::string::size_type tempsz = 0;
              char * cstr1 = new char[wholeStory[j].length() + 1];
              std::strcpy(cstr1, wholeStory[j].c_str());
              unsigned long findchoice = std::strtoul(cstr1, NULL, 0);
              delete[] cstr1;
              // unsigned long findchoice = std::stoul(wholeStory[j], &tempsz);
              if (findchoice == pagenumber) {
                std::string str2(":");
                size_t find1 = wholeStory[j].find(str2);
                size_t find2 = wholeStory[j].find(str2, find1 + 1);
                std::string transferNum =
                    wholeStory[j].substr(find1 + 1, find2 - find1 - 1);
                /*if (!isNumber(transferNum)) {
                  std::cerr << "invalid format" << std::endl;
                  exit(EXIT_FAILURE);
                }*/
                std::string transferL = wholeStory[j].substr(find2 + 1);
                std::pair<std::string, std::string> temppair(transferNum, transferL);
                Transfer.push_back(temppair);
              }
            }
          }
        }
        store.push_back(
            new page(pagenumber, page_state, pagetxt, Transfer, directory, i));
      }
    }
  }
  //
  bool contains(std::string & target) {
    char * cstr1 = new char[target.length() + 1];
    std::strcpy(cstr1, target.c_str());
    unsigned long transTonum = std::strtoul(cstr1, NULL, 0);
    delete[] cstr1;
    for (size_t i = 0; i < store.size(); i++) {
      //std::string temp = std::to_string(store[i]->getPagenum());
      if (transTonum == store[i]->getPagenum()) {
        return true;
      }
    }
    return false;
  }
  //Every page that is referenced by a choice is valid (e.g., if page 12 might send you to page 19, there needs to be a page 19 in the story).
  bool checkValidRefer() {
    for (size_t i = 0; i < store.size(); i++) {
      page temp = *store[i];
      std::vector<std::pair<std::string, std::string> > tempTrans = temp.getTrans();
      for (size_t j = 0; j < tempTrans.size(); j++) {
        std::string tempchoice = tempTrans[j].first;
        if (!contains(tempchoice)) {
          return false;
        }
      }
    }
    return true;
  }
  bool EachRefered(unsigned long & target) {
    for (size_t i = 0; i < store.size(); i++) {
      if (store[i]->getState() != 'N') {
        continue;
      }
      else {
        std::vector<std::pair<std::string, std::string> > tempTrans =
            store[i]->getTrans();
        for (size_t j = 0; j < tempTrans.size(); j++) {
          char * cstr1 = new char[tempTrans[j].first.length() + 1];
          std::strcpy(cstr1, tempTrans[j].first.c_str());
          unsigned long transTonum = std::strtoul(cstr1, NULL, 0);
          delete[] cstr1;
          if (transTonum == target) {
            return true;
          }
        }
      }
    }
    return false;
  }
  //Every page (except page 0) is referenced by at least one *other* page's choices. (e.g., if there is a page 12, then some other page must have a choice to go to page 12).
  bool checkPageRefered() {
    for (size_t i = 1; i < store.size(); i++) {
      //std::string tempPagenum = std::to_string(store[i]->getPagenum());
      unsigned long tempPagenum = store[i]->getPagenum();
      if (!EachRefered(tempPagenum)) {
        return false;
      }
    }
    return true;
  }
  //At least one page must be a WIN page and at least one page must be a LOSE page.
  bool checkWinOrLose() {
    int win = 0;
    int lose = 0;
    for (size_t i = 0; i < store.size(); i++) {
      if (store[i]->getState() == 'L') {
        lose++;
      }
      if (store[i]->getState() == 'W') {
        win++;
      }
    }
    if (win == 0 || lose == 0) {
      return false;
    }
    return true;
  }
  bool isNumber(std::string & target) {
    for (size_t i = 0; i < target.length(); i++) {
      if ((target[i] != '0') || (target[i] != '1') || (target[i] != '2') ||
          (target[i] != '3') || (target[i] != '4') | (target[i] != '5') ||
          (target[i] != '6') || target[i] != '7' || target[i] != '8' ||
          target[i] != '9') {
        return false;
      }
    }
    return true;
  }
  void UserReading() {
    page current = *store[0];
    while (true) {
      current.pageprint(false);
      if (current.getState() == 'L' || current.getState() == 'W') {
        break;
      }
      std::string input;
      unsigned long choice = 0;
      while (true) {
        std::cin >> input;
        char * cstr1 = new char[input.length() + 1];
        std::strcpy(cstr1, input.c_str());
        char * end = NULL;
        choice = std::strtoul(cstr1, &end, 0);
        delete[] cstr1;
        if (isNumber(input) || choice > current.getTrans().size() || choice <= 0) {
          std::cout << "That is not a valid choice, please try again" << std::endl;
          continue;
        }
        break;
      }
      std::string next = current.getTrans()[choice - 1].first;
      char * cstr1 = new char[next.length() + 1];
      std::strcpy(cstr1, next.c_str());
      unsigned long trans = std::strtoul(cstr1, NULL, 0);
      delete[] cstr1;
      current = *store[trans];
    }
  }
  //decide whether the node have been visited or not.
  bool IsCircle(std::vector<std::pair<int, size_t> > & target) {
    int last = target[target.size() - 1].first;
    for (size_t i = 0; i < target.size() - 1; i++) {
      if (target[i].first == last) {
        return true;
      }
    }
    return false;
  }
  //according to the ch15, store the path in the vector
  void BFSWin() {
    page current = *store[0];
    std::queue<std::vector<std::pair<int, size_t> > > BFS;
    std::pair<int, size_t> oripair(current.getIndex(), current.getTrans().size());
    std::vector<std::pair<int, size_t> > origianl;
    origianl.push_back(oripair);
    BFS.push(origianl);
    while (!BFS.empty()) {
      std::vector<std::pair<int, size_t> > currentPath = BFS.front();
      BFS.pop();
      if (IsCircle(currentPath)) {
        continue;
      }
      page currentPage = *store[currentPath[currentPath.size() - 1].first];
      if (currentPage.getState() == 'W') {
        result.push_back(currentPath);
      }
      else if (currentPage.getState() == 'L') {
        continue;
      }
      else {
        for (size_t i = 0; i < currentPage.getTrans().size(); i++) {
          std::string transTo = currentPage.getTrans()[i].first;
          char * cstr1 = new char[transTo.length() + 1];
          std::strcpy(cstr1, transTo.c_str());
          int trans = std::atoi(cstr1);
          delete[] cstr1;
          std::pair<int, size_t> temp(trans, i + 1);
          std::vector<std::pair<int, size_t> > tempPath = currentPath;
          tempPath.push_back(temp);
          BFS.push(tempPath);
        }
      }
    }
  }
  std::vector<std::vector<std::pair<int, size_t> > > & getPath() { return result; }
  void printWinpath() {
    if (result.size() == 0) {
      std::cout << "This story is unwinnable!" << std::endl;
      return;
    }
    for (size_t i = 0; i < result.size(); i++) {
      for (size_t j = 0; j < result[i].size(); j++) {
        if (j < result[i].size() - 1) {
          std::cout << result[i][j].first << "(" << result[i][j + 1].second << "),";
        }
        else {
          std::cout << result[i][j].first << "(win)" << std::endl;
        }
      }
    }
  }
  void Win() {
    BFSWin();
    printWinpath();
  }
  //step 4, a new parse function
/*
  void parseForVariable() {
    std::string st2("@");
    std::string st3("$");
    std::string st4("=");
    std::string stL("[");
    std::string stR("]");
    for (size_t i = 0; i < wholeStory.size(); i++) {
      size_t temp = wholeStory[i].find(st2);
      if (temp < wholeStory[i].length()) {
        char page_state = wholeStory[i].at(temp + 1);
        std::string pagetxt = wholeStory[i].substr(temp + 3);
        char * cstr = new char[wholeStory[i].length() + 1];
        std::strcpy(cstr, wholeStory[i].c_str());
        unsigned long pagenumber = std::strtoul(cstr, NULL, 0);
        delete[] cstr;
        std::vector<std::pair<std::string, std::string> > Transfer;
        std::vector<std::pair<std::string, std::string> > Vars;
        std::vector<std::pair<std::string, std::string> > conditions;
        if (page_state == 'N') {
          for (size_t j = 0; j < wholeStory.size(); j++) {
            //Now let me store the variable;
            size_t tempDS = wholeStory[j].find(st3);
            if (tempDS < wholeStory[i].length()) {
              char * cstr0 = new char[wholeStory[j].length() + 1];
              std::strcpy(cstr0, wholeStory[j].c_str());
              unsigned long findVar = std::strtoul(cstr0, NULL, 0);
              delete[] cstr0;
              if (findVar == pagenumber) {
                size_t tempE = wholeStory[j].find(st4);
                std::string variable =
                    wholeStory[j].substr(tempDS + 1, tempE - tempDS - 1);
                std::string value = wholeStory[j].substr(tempE + 1);
                std::pair<std::string, std::string> tempVarPair(variable, value);
                Vars.push_back(tempVarPair);
              }
              continue;
            }
            //make some change:

            size_t temp2 = wholeStory[j].find(st2);
            if (temp2 > wholeStory[j].length()) {
              //std::string::size_type tempsz = 0;
              char * cstr1 = new char[wholeStory[j].length() + 1];
              std::strcpy(cstr1, wholeStory[j].c_str());
              unsigned long findchoice = std::strtoul(cstr1, NULL, 0);
              delete[] cstr1;
              // unsigned long findchoice = std::stoul(wholeStory[j], &tempsz);
              if (findchoice == pagenumber) {
                std::string str2(":");
                size_t find1 = wholeStory[j].find(str2);
                size_t find2 = wholeStory[j].find(str2, find1 + 1);
                std::string transferNum =
                    wholeStory[j].substr(find1 + 1, find2 - find1 - 1);
                std::string transferL = wholeStory[j].substr(find2 + 1);
                std::pair<std::string, std::string> temppair(transferNum, transferL);
                Transfer.push_back(temppair);
                size_t findL = wholeStory[j].find(stL);
                size_t findR = wholeStory[j].find(stR, findL + 1);
                size_t findE = wholeStory[j].find(st4);
                //very serious problems i have not solved;
                if (findL < wholeStory[j].length() && findR < wholeStory[j].length() &&
                    findE < wholeStory[j].length()) {
                  std::string Cvar = wholeStory[j].substr(findL + 1, findE - findL - 1);
                  std::string Cvalue = wholeStory[j].substr(findE + 1, findR - findE - 1);
                  std::pair<std::string, std::string> VarPair(Cvar, Cvalue);
                  conditions.push_back(VarPair);
                }
              }
            }
          }
        }
        store.push_back(new page(
            pagenumber, page_state, pagetxt, Transfer, directory, i, Vars, conditions));
      }
    }
  }*/
    void parseForVariable1() {
      std::string st2("@");
      std::string st3("$");
      std::string st4("=");
      std::string stL("[");
      std::string stR("]");
      for (size_t i = 0; i < wholeStory.size(); i++) {
        size_t temp = wholeStory[i].find(st2);
        if (temp < wholeStory[i].length()) {
          char page_state = wholeStory[i].at(temp + 1);
          std::string pagetxt = wholeStory[i].substr(temp + 3);
          char * cstr = new char[wholeStory[i].length() + 1];
          std::strcpy(cstr, wholeStory[i].c_str());
          unsigned long pagenumber = std::strtoul(cstr, NULL, 0);
          delete[] cstr;
          std::vector<std::pair<std::string, std::string> > Transfer;
          std::vector<std::pair<std::string, std::string> > Vars;
          //std::vector<std::pair<std::string, std::string> > conditions;
            std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string> > > NewTransfer;
          if (page_state == 'N') {
            for (size_t j = 0; j < wholeStory.size(); j++) {
              //Now let me store the variable;
              size_t tempDS = wholeStory[j].find(st3);
              if (tempDS < wholeStory[i].length()) {
                char * cstr0 = new char[wholeStory[j].length() + 1];
                std::strcpy(cstr0, wholeStory[j].c_str());
                unsigned long findVar = std::strtoul(cstr0, NULL, 0);
                delete[] cstr0;
                if (findVar == pagenumber) {
                  size_t tempE = wholeStory[j].find(st4);
                  std::string variable =
                      wholeStory[j].substr(tempDS + 1, tempE - tempDS - 1);
                  std::string value = wholeStory[j].substr(tempE + 1);
                  std::pair<std::string, std::string> tempVarPair(variable, value);
                  Vars.push_back(tempVarPair);
                }
                continue;
              }
              //make some change:

              size_t temp2 = wholeStory[j].find(st2);
              if (temp2 > wholeStory[j].length()) {
                //std::string::size_type tempsz = 0;
                char * cstr1 = new char[wholeStory[j].length() + 1];
                std::strcpy(cstr1, wholeStory[j].c_str());
                unsigned long findchoice = std::strtoul(cstr1, NULL, 0);
                delete[] cstr1;
                // unsigned long findchoice = std::stoul(wholeStory[j], &tempsz);
                if (findchoice == pagenumber) {
                  std::string str2(":");
                  size_t find1 = wholeStory[j].find(str2);
                  size_t find2 = wholeStory[j].find(str2, find1 + 1);
                  std::string transferNum =
                      wholeStory[j].substr(find1 + 1, find2 - find1 - 1);
                  std::string transferL = wholeStory[j].substr(find2 + 1);
                  std::pair<std::string, std::string> temppair(transferNum, transferL);
                  //Transfer.push_back(temppair);
                  size_t findL = wholeStory[j].find(stL);
                  size_t findR = wholeStory[j].find(stR, findL + 1);
                  size_t findE = wholeStory[j].find(st4);
                  //very serious problems i have not solved;
                  if (findL < wholeStory[j].length() && findR < wholeStory[j].length() &&
                      findE < wholeStory[j].length()) {
                    std::string Cvar = wholeStory[j].substr(findL + 1, findE - findL - 1);
                    std::string Cvalue = wholeStory[j].substr(findE + 1, findR - findE - 1);
                    std::pair<std::string, std::string> VarPair(Cvar, Cvalue);
                    //conditions.push_back(VarPair);
                      std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string> > tempR(temppair,VarPair);
                      NewTransfer.push_back(tempR);
                  }else{
                      std::string Cvar("EmptyValue");
                      std::string Cvalue("0");
                      std::pair<std::string, std::string> VarPair(Cvar, Cvalue);
                      std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string> > tempR(temppair,VarPair);
                      NewTransfer.push_back(tempR);
                  }
                }
              }
            }
          }
          store.push_back(new page(
              pagenumber, page_state, pagetxt, Transfer, directory, i, Vars, NewTransfer));
        }
      }
    }
  bool containsCur(std::pair<std::string, std::string> & target) {
    if (currentVar.size() == 0) {
      return false;
    }
    for (size_t i = 0; i < currentVar.size(); i++) {
      if (target.first == currentVar[i].first) {
        return true;
      }
    }
    return false;
  }
  void replace(std::pair<std::string, std::string> & target) {
    for (size_t i = 0; i < currentVar.size(); i++) {
      if (currentVar[i].first == target.first) {
        currentVar[i].second = target.second;
      }
    }
  }
  bool correctVar(std::string & target) {
    for (size_t i = 0; i < currentVar.size(); i++) {
      if (target == currentVar[i].first) {
        return true;
      }
    }
    return false;
  }
  bool match(std::pair<std::string, std::string> & target) {
    std::string s0("0");
    if (!correctVar(target.first)) {
      if (target.second == s0) {
        return true;
      }
    }
    else {
      for (size_t i = 0; i < currentVar.size(); i++) {
        if (currentVar[i].first == target.first &&
            currentVar[i].second == target.second) {
          return true;
        }
      }
    }
    return false;
  }
  //step 4, user's input;
    bool Asnormal(std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string> > > & target){
        int count=0;
        for(size_t i=0;i<target.size();i++){
            if(target[i].second.first!="EmptyValue"){
                count++;
            }
        }
        if(count>0){
            return false;
        }
        return true;
    }
    
  void UserReadingForVar() {
    page current = *store[0];
    while (true) {
      std::vector<std::pair<std::string, std::string> > tempVar = current.getVars();
      if (tempVar.size() != 0) {
        for (size_t i = 0; i < tempVar.size(); i++) {
          if (!containsCur(tempVar[i])) {
            currentVar.push_back(tempVar[i]);
          }
          else {
            replace(tempVar[i]);
          }
        }
      }
        std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string> > > Ntrans=current.getNewTransfer();
      if (Asnormal(Ntrans)) {
        current.pageprint(false);
        if (current.getState() == 'L' || current.getState() == 'W') {
          break;
        }
      }
      else {
        current.pageprintcontent();
        if (current.getState() == 'L') {
          std::cout << "Sorry, you have lost. Better luck next time!";
          std::cout << std::endl;
          break;
        }
        if (current.getState() == 'W') {
          std::cout << "Congratulations! You have won. Hooray!";
          std::cout << std::endl;
          break;
        }
        if (current.getState() == 'N') {
          std::cout << "What would you like to do?";
          std::cout << std::endl;
          std::cout << std::endl;
          //std::vector<std::pair<std::string, std::string> > tempT = current.getTrans();
          //std::vector<std::pair<std::string, std::string> > tempC = current.getcondi();
            std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string> > > tempN=current.getNewTransfer();
          for (size_t i = 0; i < tempN.size(); i++) {
            if (tempN[i].second.first!="EmptyValue") {
              if (match(tempN[i].second)) {
                std::cout << " " << i + 1 << ". " << tempN[i].first.second << std::endl;
              }
              else {
                std::cout << " " << i + 1 << ". "
                          << "<UNAVAILABLE>" << std::endl;
              }
            }
            else {
              std::cout << " " << i + 1 << ". " << tempN[i].first.second << std::endl;
            }
          }
        }
      }
      std::string input;
      unsigned long choice = 0;
        std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string> > > tempchoice = current.getNewTransfer();
      while (true) {
        std::cin >> input;
        char * cstr1 = new char[input.length() + 1];
        std::strcpy(cstr1, input.c_str());
        char * end = NULL;
        choice = std::strtoul(cstr1, &end, 0);
        delete[] cstr1;
        if (isNumber(input) || choice > current.getNewTransfer().size() || choice <= 0) {
          std::cout << "That is not a valid choice, please try again" << std::endl;
          continue;
        }
        if (choice <= tempchoice.size() && !match(tempchoice[choice - 1].second)) {
          std::cout << "That choice is not available at this time, please try again"
                    << std::endl;
          continue;
        }
        break;
      }
      //std::string next = current.getTrans()[choice - 1].first;
        std::string next = current.getNewTransfer()[choice - 1].first.first;
      char * cstr1 = new char[next.length() + 1];
      std::strcpy(cstr1, next.c_str());
      unsigned long trans = std::strtoul(cstr1, NULL, 0);
      delete[] cstr1;
      current = *store[trans];
    }
  }
  void test() {
    for (size_t i = 0; i < wholeStory.size(); i++) {
      std::cout << wholeStory[i] << std::endl;
    }
  }
  //copy constructor
  //assign constructor

  ~story() {
    for (size_t i = 0; i < store.size(); i++) {
      delete store[i];
    }
  }
};
