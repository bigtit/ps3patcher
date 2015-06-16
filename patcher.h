#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::string;

typedef char byte;

class patcher{
  // unique_ptr<byte> pdata;
  std::vector<byte> pdata;
  char flag; // only 3b used
  bool chk_flag(char s);
  void get_pdata(string name, bool swap);
  void get_ros_pdata(string name, bool swap);
  string get_dest_name(string name);
  void write_patch(int offset, std::ofstream& out);
public:
  void set_flag(char s);
  char get_flag();
  void do_patch(string name, bool swap);

  patcher();
  ~patcher();
};
