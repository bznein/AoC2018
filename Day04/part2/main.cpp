#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

using timeSlept = map<int,int>;
using minutesSlept = map<int,vector<int>>;

int main()
{

  timeSlept ts;
  minutesSlept ms;
  int curGuard=-1;
  int last_asleep=-1;;
  auto ifs=ifstream("input.txt");
  string temp;
  string event;
  vector<string> events;
  int minutes;

  while(std::getline(ifs,temp))
    events.push_back(temp);

  std::sort(events.begin(),events.end());

  for (auto s: events)
    {
      minutes=stoi(s.substr(s.find(":")+1,2));
      event=s.substr(s.find(":")+5,s.find("#")-s.find(":")-5);
      if (event=="Guard ")
        curGuard=stoi(s.substr(s.find("#")+1,s.find(" ", s.find("#"))));
      else if (event == "falls asleep")
        {
          if (last_asleep!=-1 )
            cerr << "Not reset asleep!\n";
          last_asleep=minutes;
        }
      else if (event == "wakes up")
        {
          ts[curGuard]+=(minutes-last_asleep);
          for (int i=last_asleep; i<minutes; ++i)
            {
              if (ms.find(curGuard)==ms.end())
                ms[curGuard]=std::vector<int> (60,0);
              ms[curGuard][i]+=1;
            }
          last_asleep=-1;
        }
    }

  int max_slept=-1;
  int max_time=-1;
  for( auto const& [key, val] : ts )
    {
      if (val>max_time)
        {
          max_slept=key;
          max_time=val;
        }
    }

  int most_asleep_guard=-1;
  int most_asleep_min=-1;
  int most_asleep_freq=-1;
  for( auto const& [key, val] : ms )
    {
      int his_minute=(-std::distance(max_element(val.begin(), val.end()),val.begin()));
      int times_asleep=*(max_element(val.begin(), val.end()));
      if (times_asleep>most_asleep_freq)
        {
          most_asleep_guard=key;
          most_asleep_freq=times_asleep;
          most_asleep_min=his_minute;
        }
    }

  cout << most_asleep_guard* most_asleep_min << "\n";

}
