#ifndef __C___Test__testv__
#define __C___Test__testv__

class TestV {
protected:
    int i = 34;
    int j = 0;
    
public:
    TestV() {}
    TestV(int p_i, int p_j) : i(p_i), j(p_j) {}
    
    virtual int get_i ();
};

class TestSubV : public TestV {
public:
    int get_i ();
};

#endif /* defined(__C___Test__testv__) */
