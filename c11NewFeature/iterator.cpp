/*
 * @Author: Jasper
 * @Date: 2021-09-02 22:24:06
 * @LastEditTime: 2021-12-04 23:27:32
 * @LastEditors: Please set LastEditors
 * @Description: The container Iterator stuff 
 * @FilePath: /algorithm/c11NewFeature/iterator.cpp
 */

//g++ -std=c++11 -pthread  -o mm iterator.cpp

/*
1. if the container is empty the begin() and end() function is Null iterator
2. the rbegin() and rend() (have demo)
   
   反向迭代器rbegin 指向最后一个元素，而rend 是指向第一个元素的前面，
3. const_iterator
   can't modify the value of this iterator point to
*/

#include <iostream>
#include <stdio.h>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Student
{
public:
    void setAge(const int &age)
    {

        this->age = age;
        std::cout << "father's print age:" << age << std::endl;
    };

private:
    void getAge(){};

private:
    int age;
};

class firstGrade : private Student
{
public:
    void setAge(const int &age)
    {
        Student::setAge(age);
        //getAge();
    }
};

int main()
{
    firstGrade stu;

    stu.setAge(10);

    // vector<int> num{10, 20, 30};

    // //the reverse iterator shows
    // for (vector<int>::reverse_iterator rit = num.rbegin(); rit != num.rend(); rit++)
    // {
    //     cout << *rit << endl;
    // }
}