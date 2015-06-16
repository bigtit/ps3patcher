#include <iomanip>
#include "patcher.h"
#include <getopt.h>

string appname;

void show_help(){
  std::cout << "Usage: " << appname << " options [inputfile]" << std::endl;
  std::cout << " -h --help" << std::setw(40) << "Display help information." << std::endl;
  std::cout << " -t --trvk" << std::setw(40) << "Set the trvkpatches flag." << std::endl;
  std::cout << " -f --force" << std::setw(38) << "Set the forcepatch flag." << std::endl;
  std::cout << " -a --autoexit" << std::setw(33) << "Set the autoexit flag." << std::endl;
  std::cout << " -s --swap" << std::setw(38) << "Enable the swap option." << std::endl;
}

int main(int argc, char** argv){
  int next_op;
  const char* const short_op = "htfas";
  const struct option long_op[] = {
    {"help", 0, NULL, 'h'},
    {"trvk", 0, NULL, 't'},
    {"force", 0, NULL, 'f'},
    {"autoexit", 0, NULL, 'a'},
    {"swap", 0, NULL, 's'},
    {NULL, 0, NULL, 0}
  };

  patcher p;
  bool is_swap = false;

  appname = argv[0];
  do{
    next_op = getopt_long(argc, argv, short_op, long_op, NULL);
    switch(next_op){
      case 'h':
        show_help();
        break;
      case 't':
        p.set_flag(0x1);
        break;
      case 'f':
        p.set_flag(0x2);
        break;
      case 'a':
        p.set_flag(0x4);
        break;
      case 's':
        is_swap = true;
        break;
      case -1:
        break;
      default:
        break;
    }
  }while(next_op!=-1);

  if(optind >= argc){ 
    show_help();
    return 1;
  }

  std::cout << "flag: " << (int)p.get_flag() << std::endl;
  std::cout << "input file: " << argv[optind] << std::endl;

  // run
  p.do_patch(argv[optind], is_swap);

  return 0;
}

