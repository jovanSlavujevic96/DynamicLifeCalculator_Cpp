/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <cstdio>
#include <cmath>
#include <cassert>

#include <iostream>
#include <string>
#include <vector>

template<typename T>
struct NumWrap
{
    T val;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const NumWrap<T>& num)
{
    const auto vdbl = static_cast<double>(num.val);
    const auto vrnd = static_cast<double>(std::floor(num.val));
    
    const auto diff = vdbl - vrnd;
    const auto diffby100 = std::round(diff * 100.0);
    
    auto vfirst = std::to_string(static_cast<int>(vrnd));
    assert(vfirst.size() <= 4);
    vfirst.insert(vfirst.begin(), 4-vfirst.size(), '0');
    
    auto vsecond = std::to_string(static_cast<int>(diffby100));
    assert(vsecond.size() <= 2);
    vsecond.insert(vsecond.begin(), 2-vsecond.size(), '0');
    
    
    os << vfirst << "." << vsecond;
    return os;
}

template<typename T>
T sum(const std::vector<T>& v)
{
    T ret{};
    for (const auto vv : v)
    {
        ret += vv;
    }
    return ret;
}

template<typename T>
void print(const std::vector<T>& v)
{
    std::cout << "printing vector" << std::endl;
    int ctr = 0;
    for (const auto vv : v)
    {
        if (ctr == 5)
        {
            ctr = 0;
            std::cout << std::endl;
        }
        std::cout << NumWrap<T>{vv} << " ";
        ctr++;
    }
    std::cout << std::endl;
}


std::vector<float> processIncomes(const std::vector<float>& incomes)
{
    std::vector<float> ret;
    std::vector<float> diff;
    
    ret.push_back(incomes.front());
    diff.push_back(incomes.front() - ret.front());
    for(size_t i=1, end=incomes.size(); i<end; i++)
    {
        auto val = incomes[i];

        if (incomes[i-1] < 2000)
        {
            if (ret[i-1] < 2000)
            {
                val = 0;
            }
            else
            {
                val += diff.back();
            }
        }

        if (val < 2000)
        {
            if ((i+1) < end)
            {
                if ((incomes[i+1] + val) < 2000)
                {
                    val += incomes[i+1];
                }
                else
                {
                    val = 2000;
                }
            }
        }

        if (val < 0)
        {
            val = 0;
        }
        
        ret.push_back(val);
        diff.push_back(incomes[i] - ret[i] + diff.back());
    }
    
    return ret;
}

int main()
{
    const std::vector<float> input = {
        2000.0, 2182.86, 2345.01, 2107.79, 2137.09, 2227.84, 1604.95, 1962.59, 450.96
    };
    print(input);
    std::cout << "sum: " << sum(input) << std::endl;
    
    std::cout << std::endl;
    
    const auto output = processIncomes(input);
    print(output);
    std::cout << "sum: " << sum(output) << std::endl;

    return 0;
}