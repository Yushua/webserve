
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

std::vector<std::string> configSplit(std::string string, const char *str)
{
    vector<std::string> vec;
    int length = string.length();
    int subl = strlen(str);
    int i = 0;
    bool value = true;

    /*
    checks if the sequence,
    when the string[i] equals the first character in the sequence
    then it will go through, if somewhere it fails, then it stops.
    only when all of them compare, does it elave the false bool
    and leaves the while.
    */
    while (i < length && value == true)
    {
        if (string[i] == str[0]) {
            for (int y = 0; str[y] && value == true; y++) {
                if (string[i] == str[y])
                    value = false;
                else {
                    value = true;
                    break;
                }
            }
        }
        i++;
    }
    vec.push_back(string.substr(0, i - 1));
    if (static_cast<unsigned long>(i + 1) == string.length())
        vec.push_back("");
    else
        vec.push_back(string.substr(i + subl - 1, length - subl - i + 1));
    return(vec);
}
