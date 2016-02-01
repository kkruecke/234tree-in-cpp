#ifndef depth_tracker_h
#define depth_tracker_h

#include <iostream>

class DepthTracker {
  private:
       int depth;
  public:
      DepthTracker() : depth{0} {}
      DepthTracker(const DepthTracker& lhs) : depth{lhs.depth + 1} {}
     ~DepthTracker() {}
      void operator()(int key);
};

inline void DepthTracker::operator()(int key)
{
  std::cout << "key = " << key << " is at depth " << depth << std::endl;
}
#endif
