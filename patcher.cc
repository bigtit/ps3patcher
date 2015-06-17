#include <utility>
#include <cstdio> // __LINE__
#include "patcher.h"
#include "pbase.h"

patcher::patcher():flag(0){}
patcher::~patcher(){}

void patcher::set_flag(char s){
  flag |= s;
}
char patcher::get_flag(){
  return flag;
}
bool patcher::chk_flag(char s){
  return (flag & s);
}

void status(string str){
  std::cout << str << std::endl;
}
#define error(str) \
  std::cout << __FILE__ << ", " << __LINE__ << ": " << str << std::endl;

void patcher::get_pdata(string name, bool swap){
  std::ifstream freader(name.c_str(), std::ios::binary|std::ios::ate);
  freader >> std::noskipws;
  auto pos = freader.tellg();
  std::vector<byte> tmp(pos);

  freader.seekg(0, std::ios::beg);
  freader.read(&tmp[0], pos);
  if(swap) pbase::swap_bytes(tmp); // swap_byte(vector<byte>&, pos_type)

  pdata = std::move(tmp); // c++11 dafahao
  return;
}
void patcher::get_ros_pdata(string name, bool swap){
  get_pdata(name, swap);
}

string patcher::get_dest_name(string name){
  return name+".out";
}

void patcher::write_patch(int offset, std::ofstream& out){
  out.seekp(offset, std::ios::beg);
  out.write((const char*)&pdata[0], pdata.size());
  std::cout << "patchdata size: " << pdata.size() << " bytes" << std::endl;
}

void patcher::do_patch(string name, bool swap){
  status("Go processing...");
  if(swap) status("Go swap");
  string fileout = get_dest_name(name);
  std::ifstream freader(name.c_str(), std::ios::binary);
  freader >> std::noskipws;
  std::ofstream fwriter(fileout.c_str(), std::ios::binary);
  status("Creating output file...");
  fwriter << freader.rdbuf(); // copy
  freader.seekg(0, std::ios::end);
  auto pos = freader.tellg();
  freader.close();
  get_ros_pdata("patch.bin", swap);
  if(0x1000000L == pos){ // nor
    status("Go NOR");
    write_patch(0xc0010, fwriter);
    write_patch(0x7c0010, fwriter);
    if(chk_flag(0x1)){
      status("Go trvkpatches");
      get_pdata("nor_rvk.bin", swap);
      write_patch(0x40000, fwriter);
    }
    if(chk_flag(0x2)){
      status("Go forcepatch && rosheader");
      get_pdata("ros_head.bin", swap);
      write_patch(0xc0000, fwriter);
      write_patch(0x7c0000, fwriter);
    }
    status("Done NOR");
  }else if(0x10000000L == pos){ // nand
    status("Go NAND");
    write_patch(0xc0030, fwriter);
    write_patch(0x7c0020, fwriter);
    if(chk_flag(0x1)){
      status("Go trvkpatches");
      get_pdata("nand_rvk.bin", swap);
      write_patch(0x40000, fwriter);
    }
    if(chk_flag(0x2)){
      status("Go forcepatch && rosheader");
      get_pdata("ros_head.bin", swap);
      write_patch(0xc0020, fwriter);
      write_patch(0x7c0010, fwriter);
    }
    status("Done NAND");
  }else{
    error("Size error, exiting");
    remove(fileout.c_str());
    return;
  }
  if(chk_flag(0x4)); // autoexit, reserved
  return;
}
