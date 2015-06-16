#include "pbase.h"

bool pbase::swap_bytes(std::vector<byte>& pdata){
  if(!pdata.size()%2) return false;
  for(int i=0; i<pdata.size(); i+=2)
    std::swap(pdata[i], pdata[i+1]);
}
