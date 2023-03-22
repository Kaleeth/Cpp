// CppCon 2018 Multimap C++11

#include<map>
#include<string>
#include<iostream>

int main()
{
    using namespace std;

    multimap<string, string> dict
    {
	    {"string", "one"},
	    {"string", "two"}
    };

    for (const auto& el : dict)
    {
	cout << el.first << " " << el.second << endl;
    }
}
