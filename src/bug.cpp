/*
 This reproduces a bug in new-tree234.h. The output repeats then soon afterward iterator::pop() throws an exception.
 */
template<class Key, class Value> void test(const tree234<Key, Value>& tree, ostream& ostr)
{
   // This has a  bug. 
   auto rend = tree.rend();
   
   auto riter = tree.rbegin();
   
   auto i = 1;
   
   while (riter != rend) {

      auto&& pr = *riter;

      ostr << pr.first << ", " << flush;
      
      if (pr.first == 97 || pr.first == 92 ) {

    	  auto debug = 10;
    	  ++debug;
      }   
     ++riter; /

      
     ++i;
   }
  
}

int main(int argc, char** argv)
{
  tree234<int, int> tree = { {60, 60}, {30, 30}, {10, 10}, {20, 20}, {50, 50}, {40, 40}, {70, 70}, {80, 80}, {15, 15}, {90, 90}, {0, 0}, {27, 27}, {62, 62}, {87, 87}, {37, 37}, {92, 92}, {79, 79}, {23, 23}, {17, 17}, {97, 97}, {55, 55}, {51, 51}, {69, 69}, {1, 1}, {2, 2}, {33, 33}, {26, 26}, {15, 15}, {5, 5}};
  
  vector< pair<int,int> > append  = { {60, 60}, {30, 30}, {10, 10}, {20, 20}, {50, 50}, {40, 40}, {70, 70}, {80, 80}, {15, 15}, {90, 90}, {0, 0}, {27, 27}, {62, 62}, {87, 87}, {37, 37}, {92, 92}, {79, 79}, {23, 23}, {17, 17}, {97, 97}, {55, 55}, {51, 51}, {69, 69}, {1, 1}, {2, 2}, {33, 33}, {26, 26}, {15, 15}, {5, 5}}; 
  
  for (auto& pr : append) {
        
        tree.insert(pr.first, pr.second);
  }
  
  return 0;
}
