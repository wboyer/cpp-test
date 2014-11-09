#include <iostream>
using namespace std;

class Test {
protected:
    int i = 33;
    int j = 0;
    
public:
    Test() {}
    Test(int p_i, int p_j) : i(p_i), j(p_j) {}

    int get_i () {
        return i;
    };
};

class TestSub : public Test {
public:
    int get_i () {
        return i * 1000;
    };
};

int main(int argc, const char * argv[]) {
    cout << "Hellooo, World!" << endl;

    constexpr int x = 5 + 6;
    cout << x << endl;
    
    int *y = nullptr;
    int a = 77;

    y = &a;
    cout << *y << endl;

    int const b = 888;
    cout << b << endl;

    int & h = *y;
    h = b;
    cout << h + 3 << endl;
    cout << *y << endl;
    cout << a << endl;
    
    int *g = new int;
    *g = 45;
    cout << *g << endl;
    delete g;
    
    Test *t = new Test;
    cout << t->get_i() << endl;
    delete t;

    t = new Test{77, 88};
    cout << t->get_i() << endl;
    delete t;

    t = new TestSub;
    cout << t->get_i() << endl;
    delete t;
    
    TestSub *s = new TestSub;
    cout << s->get_i() << endl;
    delete s;
    
    return 0;
}
