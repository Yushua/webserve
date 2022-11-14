#include <message.hpp>
#include <ft_lib.hpp>

string message::getHeader(string name) {
    map<string, string>::const_iterator found = headers.find(ft_to_lower(name));
    if (found == headers.cend())
        return "";
    return found->second;
}
