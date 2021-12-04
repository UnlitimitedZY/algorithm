/*
 * @Author: your name
 * @Date: 2021-12-04 22:07:05
 * @LastEditTime: 2021-12-04 23:20:57
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /algorithm/The design model /The strategy mode/demo.h
 */
#include <iostream>

using std::cout;
using std::endl;

enum class duckEnum
{
    MALLARDUCK,
    MODELDUCK
};

//把变化的行为给抽象出来
class flyBehaviour
{
public:
    virtual void fly() = 0;
};

class flyNoWay : public flyBehaviour
{
public:
    void fly() { cout << "can't fly" << endl; }
};

class flyWing : public flyBehaviour
{
public:
    void fly() { cout << "can fly with wing" << endl; }
};

class quackBehaviour
{
public:
    virtual void quack() = 0;
};

class Quack : public quackBehaviour
{
public:
    void quack() { cout << "can quack" << endl; }
};

class quackNoWay : public quackBehaviour
{
public:
    void quack() { cout << "can't quack" << endl; }
};

class Duck
{
public:
    virtual void display() = 0;
    virtual ~Duck() = default;
    void flyWhitch() { itsQuack->quack(); };
    void quackWhitch() { itsFly->fly(); };

protected:
    quackBehaviour *itsQuack;
    flyBehaviour *itsFly;
};
class ModelDuck : public Duck
{
public:
    ModelDuck()
    {
        itsQuack = new quackNoWay();
        itsFly = new flyNoWay();
    }
    void display() { cout << "I'm ModelDuck" << endl; }
};

class MallarDuck : public Duck
{

public:
    MallarDuck()
    {
        itsQuack = new Quack();
        itsFly = new flyWing();
    }
    ~MallarDuck()
    {
        delete itsQuack;
        delete itsFly;
    }
    void display()
    {
        cout << "I'm Mallar Duck" << endl;
    }
};

int main()
{
    ModelDuck model;
    model.display();
    model.flyWhitch();
    model.quackWhitch();

    cout << "---------------------------------" << endl;
    MallarDuck Mallar;
    Mallar.display();
    Mallar.flyWhitch();
    Mallar.quackWhitch();
}