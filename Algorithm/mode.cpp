#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>

using namespace std;

int main()
{
    freopen("input.txt","r", stdin);
    freopen("output.txt","w", stdout);


    map<int,int> number_count;

    int number;
    while(input >> number)
    {
        ++number_count[number];
    }

    map<int,int>::iterator map_it  = number_count.begin();

    map_it++;
    int key = map_it->first;
    int maxcount = map_it->second;
    while(map_it != number_count.end())
    {
        if (maxcount < map_it->second)
        {
            maxcount = map_it->second;
            key = map_it->first;
        }
        ++map_it;
    }

    output<<key<<endl<<maxcount;

    return 0;
}
