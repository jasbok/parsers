#include "std/fileutil.h"
#include "tidy/tidy++.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    string html;
    file_util::read_all("/home/stevo/simcity+2000.html", html);

    tidy_cpp tidy(html);
    tidy.set_option(TidyHtmlOut, true);
    tidy.set_option(TidyForceOutput, true);

    tidy.parse();
    tidy.clean_and_repair();
    tidy.run_diagnostics();

    tidy.filter([](TidyNode node){
        string name = tidy_cpp::name(node);
        return name.compare("script") != 0 && name.compare("comment") != 0;
    });
    tidy.save_buffer();

    cout << tidy.output() << endl;

    return 0;
}
