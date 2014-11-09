#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <future>
#include <fstream>

#include "test.h"
#include "testv.h"

using namespace std;

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
