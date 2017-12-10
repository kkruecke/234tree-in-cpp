               
constexpr const std::pair<const Key, Value>& constkey_pair(int i) const { return  {static_cast<const Key>(pairs[i].first), pairs[i].second}; } // C++17 initialization. Does this invoke copy ctor?

constexpr std::pair<const Key, Value>& constkey_pair(int i) { return  {static_cast<const Key>(pairs[i].first), pairs[i].second}; } // C++17 initialization. Does this invoke copy ctor?


