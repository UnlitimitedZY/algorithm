/*
 * @Author: Jasper
 * @Date: 2021-09-02 22:24:06
 * @LastEditTime: 2021-09-02 22:48:01
 * @LastEditors: Please set LastEditors
 * @Description: The container Iterator stuff 
 * @FilePath: /algorithm/c11NewFeature/iterator.cpp
 */

//g++ -std=c++11 -pthread  -o mm iterator.cpp

/*
1. if the container is empty the begin() and end() function is Null iterator
2. the rbegin() and rend() (have demo)

*/

#include <iostream>
#include <stdio.h>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> num{10, 20, 30};

    //the reverse iterator shows
    for (vector<int>::reverse_iterator rit = num.rbegin(); rit != num.rend(); rit++)
    {
        cout << *rit << endl;
    }
}