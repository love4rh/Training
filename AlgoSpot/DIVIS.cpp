/*
https://algospot.com/judge/problem/read/DIVIS
1v3
2P6
IsThisDivisible
end

yes
no
no
*/
#include <iomanip>
#include <iostream>
#include <cmath>
#include <string>


using namespace std;

istream& in = cin;
ostream& out = cout;


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);

    string digit;

    while( true )
    {
        in >> digit;

        if( digit == "end" )
            break;

        int dec = 0;
        for(int i = 0; i < (int) digit.size(); ++i)
        {
            char ch = digit.at(i);

            if( '0' <= ch && ch <= '9')
            {
                dec += ch - 48; // - 48 + 0
            }
            else if( 'A' <= ch && ch <= 'Z')
            {
                dec += ch - 55; // - 65 + 10
            }
            else if( 'a' <= ch && ch <= 'z')
            {
                dec += ch - 61; // - 97 + 36
            }

            // 2x(62) = 2x(61+1) --> 2
            // 2x(62^2) = 2x(61+1)^2 = 2x(61^2+2x61+1) --> 2
            dec %= 61;
        }

        out << ((dec % 61) == 0 ? "yes" : "no") << "\n";
    }

    return 0;
}
