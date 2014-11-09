#ifndef C___Test_test_h
#define C___Test_test_h

class Test {
protected:
    int i = 33;
    int j = 0;
    
public:
    Test() {}
    Test(int p_i, int p_j) : i(p_i), j(p_j) {}
    
    int get_i ();
};

class TestSub : public Test {
public:
    int get_i ();
};

#endif
