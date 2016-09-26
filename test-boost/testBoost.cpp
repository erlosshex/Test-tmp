#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

int main()
{
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;
    std::cout<<"testing, please input the string: "<<std::endl;
    std::for_each(in(std::cin),in(),std::cout<<(_1*3)<<" ");
    std::cout<<"testing done!"<<std::endl;
    return 0;
}

