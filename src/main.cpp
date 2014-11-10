#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <future>
#include <fstream>

#include "test.h"
#include "testv.h"

using namespace std;

template<typename T>
void f(T o) {
    cout << o << endl;
}

template<typename T>
class equals {
    const T val;
public:
    equals() : val(0) {}
    equals(const T & v) : val(v) {}
    bool operator() (const T & o) const { return (o == val); };
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
    
    // templates
    f<int> (7);
    f<string> ("hi");
    f<bool> (false);
    
    equals<int> e0;
    cout << e0(0) << endl;
    
    equals<int> e6 {6};
    cout << e6(6) << endl;

    equals<int> e7 (7);
    cout << e7(6) << endl;
    cout << e7(7) << endl;
    
    // concurrency and file input/output
    queue<char> q;
    string fn = "out.txt";
    ofstream st(fn);
    mutex qm;
    
    string str = "abcdefghijklmnopqrstuvwxyz";
    
    cout << "writing \"" << str << "\" to " << fn << "..." << endl;
    
    for (char c: str)
        q.push(c);
 
    auto l = [&q, &st, &qm]() {
        while (true) {
            unique_lock<mutex> lock { qm };
            
            if (q.empty())
                return;
            
            char c = q.front();
            st << c;
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

    st << endl;
    st.close();
    
    cout << "done!" << endl;
    cout << "contents of " << fn << ":" << endl;
    
    int constexpr bs = 1024;

    char *buf = new char[bs];
    // unique_ptr<char []> buf = { new char[bs] }; Why won't getline() accept this below?
    
    ifstream is(fn);

    while (is.getline(buf, bs))
        cout << buf << endl;

    is.close();

    return 0;
}
