#include <cstring>
#include <bits/stdc++.h> 
#include "../header/utility.hpp"




std::vector<std::string> mh::utility::split(const std::string& str , const char delimeter)
{
    std::vector<std::string> vect; 
    std::stringstream ss(str);
    std::string token;

    while(getline(ss, token , ','))
    {
        vect.push_back(token);
    }

    return vect;    
}


void mh::utility::hello()
{
    std::cout << "hello" << std::endl;
}