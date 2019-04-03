#include <fstream>
#include <iostream>
#include <vector>
#include <string>


void read(std::ifstream& ifs,std::vector<std::vector<double>>& data){
  ifs.ignore(1000,'\n');
  std::string tmps;
  int tmpi;
  ifs >> tmps;
  if(!ifs.good() or tmps.size()<3) return;
  tmpi = tmps.size()-3;
  std::cout << tmps.substr(1,tmpi) << std::endl;
  data[0].push_back(std::stod(tmps.substr(1,tmpi)));
  ifs.ignore(1000,'\n');
  for(auto it = data.begin()+1; it!=data.end()-1; ++it ){
    ifs >> tmps >> tmps;
    tmpi = tmps.size()-1;
    std::cout << tmps.substr(0,tmpi) << std::endl;
    it->push_back(std::stod(tmps.substr(0,tmpi)));
    ifs.ignore(1000,'\n');
  }
  ifs >> tmps >> tmps;
  std::cout << tmps << std::endl;
  data[data.size()-1].push_back(std::stod(tmps));
  ifs.ignore(1000,'\n');
}

int main(){

  std::ifstream in("elasrunlist.json");
  std::vector<std::vector<double>> data(10);
  while (in.good()){
    read(in,data);
  }

  std::cout <<data[0].size()<<std::endl;
  for( auto& line: data){
    for( auto& word: line){
      std::cout << word << '\t';
    }
    std::cout << '\n';
  }

}
