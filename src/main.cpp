#include "vlc_client.h"
#include <iostream>
#include <cstdlib>


int main(int argc , char** argv) {

    if(argc == 1 ) {

        std::cerr << "Usage : media_path times_play.\n";
        exit(1);
    }

    std::string file_path = argv[1];

    /*
     * This count variable is the times the media file will be played.
     * if nothing is given , only one time the file will be played.
     * Than again , whats the point of running the program if you
     * just whan to play it once !!
     */


    int count;


    if(argc == 3)
        count = atoi(argv[2]);
    else
        count = 1;

    std::cout << file_path << " " << count << "\n";

    Client::VLC vlc_client(file_path , count);
    vlc_client.run();

    return 0;
}
