#include <iomanip>
#include "patcher.h"
#include <getopt.h>
using std::cout;
using std::setw;
using std::endl;

string appname = "tmain";

void show_help(){
  cout << "Usage: " << appname << " options [inputfile]" << endl;
  cout << " -h --help" << setw(40) << "Display help information." << endl;
  cout << " -t --trvk" << setw(40) << "Set the trvkpatches flag." << endl;
  cout << " -f --force" << setw(38) << "Set the forcepatch flag." << endl;
  cout << " -a --autoexit" << setw(33) << "Set the autoexit flag." << endl;
  cout << " -s --swap" << setw(38) << "Enable the swap option." << endl;
  cout << " -d --debug" << setw(30) << "Show debug info." << endl;
}

int main(int argc, char** argv){
  int next_op;
  const char* const short_op = "htfasd";
  const struct option long_op[] = {
    {"help", 0, NULL, 'h'},
    {"trvk", 0, NULL, 't'},
    {"force", 0, NULL, 'f'},
    {"autoexit", 0, NULL, 'a'},
    {"swap", 0, NULL, 's'},
    {"debug", 0, NULL, 'd'},
    {NULL, 0, NULL, 0}
  };

  bool is_swap = false;
  bool is_debug = false;
  char flag = 0;

  appname = argv[0];
  do{
    next_op = getopt_long(argc, argv, short_op, long_op, NULL);
    switch(next_op){
      case 'h':
        show_help();
        break;
      case 't':
        flag |= 0x1;
        break;
      case 'f':
        flag |= 0x2;
        break;
      case 'a':
        flag |= 0x4;
        break;
      case 's':
        is_swap = true;
        break;
      case 'd':
        is_debug = true;
        break;
      case -1:
      default:
        break;
    }
  }while(next_op!=-1);

  if(optind >= argc){ 
    show_help();
    return 1;
  }

  patcher p(is_debug);
  p.set_flag(flag);
  // cout << "flag: " << (int)p.get_flag() << endl;
  cout << "input file: " << argv[optind] << endl;

  // run
  p.do_patch(argv[optind], is_swap);

  return 0;
}

