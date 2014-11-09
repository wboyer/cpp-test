#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <future>

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
    }
};

class TestSub : public Test {
public:
    int get_i () {
        return i * 1000;
    }
};

class TestV {
protected:
    int i = 34;
    int j = 0;
    
public:
    TestV() {}
    TestV(int p_i, int p_j) : i(p_i), j(p_j) {}
    
    virtual int get_i () {
        return i;
    }
};

class TestSubV : public TestV {
public:
    int get_i () override {
        return i * 1000;
    }
};

int main(int argc, const char * argv[])
{
    cout << "Hellooo, World!" << endl;
    
    // constexpr
    constexpr int x = 5 + 6;
    cout << x << endl;
    
    // pointer
    int *y = nullptr;
    int a = 77;
    
    y = &a;
    cout << *y << endl;
    
    // reference
    int const b = 888;
    cout << b << endl;
    
    int & h = *y;
    h = b;
    cout << h + 3 << endl;
    cout << *y << endl;
    cout << a << endl;
    
    // allocation
    int *g = new int;
    *g = 45;
    cout << *g << endl;
    delete g;
    
    // custom class
    Test *t = new Test;
    cout << t->get_i() << endl;
    delete t;
    
    // constructor
    t = new Test{77, 88};
    cout << t->get_i() << endl;
    delete t;
    
    // subclass
    t = new TestSub;
    cout << t->get_i() << endl;
    delete t;
    
    TestSub *s = new TestSub;
    cout << s->get_i() << endl;
    delete s;
    
    // collection
    vector<Test> v = { Test(55,66) };
    cout << v.at(0).get_i() << endl;
    
    for (Test t: v)
        cout << t.get_i() << endl;
    
    v.push_back(TestSub());
    
    for (Test t: v)
        cout << t.get_i() << endl;
    
    // polymorphism
    TestV *sv = new TestSubV;
    cout << sv->get_i() << endl;
    delete sv;
    
    // collection must contain pointers, otherwise object slicing
    vector<TestV *> vv = { new TestV(56,67) };
    cout << vv.at(0)->get_i() << endl;
    
    for (TestV *t: vv)
        cout << t->get_i() << endl;
    
    vv.push_back(new TestSubV());
    
    for (TestV *t: vv)
        cout << t->get_i() << endl;

    // unique_ptr
    unique_ptr<TestV> usv { new TestSubV };
    cout << usv->get_i() << endl;
    
    // concurrency
    queue<char> q;
    mutex qm;

    string str = "abcdefghijklmnopqrstuvwxyz";
    
    for (char c: str)
        q.push(c);
 
    auto l = [&q, &qm]() {
        while (true) {
            unique_lock<mutex> lock { qm };
            
            if (q.empty())
                return;
            
            char c = q.front();
            cout << c << endl;
            q.pop();
            
            lock.unlock();
            
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    };
    
    future<void> f1 = async(l);
    future<void> f2 = async(l);
    future<void> f3 = async(l);
    future<void> f4 = async(l);
    
    f1.get();
    f2.get();
    f3.get();
    f4.get();
    
    return 0;
}
