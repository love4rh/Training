/*
https://algospot.com/judge/problem/read/JEONGLIBE
9
Above and Beyond Feat Zoe Johnston - Alchemy (Above and Beyond Club Mix).mp3
Coldplay - Every Teardrop Is A Waterfall (Swedish House Mafia Remix).mp3
/Andrew Rayel/Armin Van Buuren - Serenity (Andrew Rayel Aether Remix).mp3
Armin Van Buuren - Serenity (Andrew Rayel Aether Remix).mp3
/Above and Beyond Feat Zoe Johnston - Alchemy/Above and Beyond Feat Zoe Johnston - Alchemy (Above and Beyond Club Mix).mp3
Nuera - Transatlantic 2009 (Original Mix).mp3
/Discograph/Nuera/Nuera - Transatlantic 2011 (Original Mix).mp3
/Alex M O R P H - Eternal Flame (Alex M O R P H s Reach Out For The Stars Mix).mp3
01. Armin Van Buuren Feat Fiora - Waiting For The Night (Radio Edit).mp3

7
*/

#include <iostream>
#include <set>
#include <string>

using namespace std;

istream& in = cin;
ostream& out = cout;

// 0: not separator, 1: "_", 2: ". ", 3: " - "
int isSeparator(const string& name, int pos)
{
    if( name[pos] == '_' )
        return 1;
    else if( name[pos] == '.' && name[pos + 1] == ' ')
        return 2;
    else if( name[pos] == ' ' && name[pos + 1] == '-' && name[pos + 2] == ' ')
        return 3;

    return 0;
}

string extract(const string& name)
{
    string splits[4];

    int s = 0;
    // all of names has ".mp3" as sufix, so we don't need consider it.
    for(int i = 0; i < (int) name.size() - 4; ++i)
    {
        const char ch = name[i];
        int sepType = isSeparator(name, i);

        if( sepType > 0 )
        {
            s += 1;
            i += (sepType - 1);
        }
        else
            splits[s] += char(ch < 97 ? ch : ch - 97 + 65);
    }

    s = s == 1 ? 0 : 1;

    return splits[s] + "/" + splits[s + 1];
}


int main(int argc, char* argv[])
{
    int N;

    in >> N;

    string filePath;
    set<string> music;

    getline(in, filePath); // skip the line of music count

    while( N-- )
    {
        getline(in, filePath);

        int dirSep = filePath.rfind("/");

        music.insert( extract(dirSep != -1 ? filePath.substr(dirSep + 1) : filePath) );
    }

    out << music.size() << "\n";

    return 0;
}
