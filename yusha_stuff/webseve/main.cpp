/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 21:13:58 by ybakker       #+#    #+#                 */
/*   Updated: 2022/09/17 21:44:48 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void error_exit(std::string error)
{
	std::cerr << error << " error!\n";
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    std::string default_conf = "./config/default_config";
    if (argc == 1)
    {
        WebServer<PollModule> web_server(config);
        web_server.Run();
    }
    else
    {
        std::cerr << "input error argc-(" << argc << ")\n" << std::endl;
        exit(EXIT_FAILURE);
    }
    return (0);
}
/*

"/seasonal/index-fall.html

parameters:
sometimes you require passwords and a username, si that the case here? its a simple addition to everything
at the end ;type=d is this important? it tells what type of info you're sending
this ; > can be anyhting, liek graphics=true. ifnormaiton that comes from paremeters

Query, is ?
different form ;. 
it checks if it is in there

fragments = #


*/
