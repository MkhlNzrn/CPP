#include <iostream>
#include <gtest/gtest.h>

template<int ...T>
class poly{
private:
    constexpr int Pow(int x, int y)const{
        int res = 1;
        for (int i = 0; i < y; ++i)
            res *= x;
        return res;
    }
    int coef[sizeof...(T)] = {(T)...};
    int size;
public:
    constexpr int getx(const int x){
        int sum = 0;
        for (int i = 0; i < sizeof...(T); ++i)
            sum +=coef[i] * Pow(x , i);
        return sum;
    }

    friend std::ostream& operator <<(std::ostream &s, const poly &a){
        for (int i = 0; i < a.size; ++i){
            s << a.coef[i] << std::endl;
        }
        return s;
    }


};

TEST(TestCaseName, TestName){
    EXPECT_EQ((poly<2, 3, 3>{}.getx(0)), 2);
}


int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}