#include "vlc_client.h"
#include <stdexcept>
#include <iostream>
#include <unistd.h>


namespace Client {

    libvlc_event_manager_t* VLC::m_event_manager = nullptr;

    VLC::VLC(const std::string& file_path , int count):m_count(count) {

        init_instance();
        load_file(file_path);
        //attach_event(); we are commenting this out because we dont want to handle event at the moment.
    }

    VLC::~VLC() {


        if(m_player != nullptr) 
            libvlc_media_player_release(m_player);
        

        if(m_instance != nullptr) 
            libvlc_release(m_instance);

    }

    void VLC::init_instance() {


        m_instance = libvlc_new(0 , nullptr);

        if(m_instance == nullptr)
            throw std::runtime_error("Could not initialize vlc!!");
    }
    
    
    void VLC::load_file(const std::string& file_path) {

        m_media_file = libvlc_media_new_path(m_instance , file_path.c_str());


        if(m_media_file == nullptr)
            throw std::runtime_error("Could not load media file !!");

        m_player = libvlc_media_player_new_from_media(m_media_file);

        if(m_player == nullptr)
            throw std::runtime_error("Could not load media file !!");


        std::cout << "File is loaded.\n";


        libvlc_media_release(m_media_file);
    }

    void VLC::run() {

        for(unsigned int i = 0 ; i < m_count; i++){
            std::cout << "************************************************\n";
            std::cout << "Playing " << i + 1 << " / " << m_count << " times.\n ";
            std::cout << "************************************************\n";
            play();
        }

    }

    
    void VLC::player_position_callback(const libvlc_event_t* event , void* params) {
        std::cout << "Position is : " << event->u.media_player_position_changed.new_position << "\n";

    }

    void VLC::attach_event() {

        m_event_manager = libvlc_media_player_event_manager(m_player);
        libvlc_event_attach(m_event_manager , libvlc_MediaPlayerPositionChanged , player_position_callback , nullptr);
    }

    void VLC::play() {


        int waiting_time = 1; // vlc needs some time to initialize.Here we add 1 milisecond to initialize it.
        libvlc_media_player_play(m_player);
        sleep(waiting_time);


        while(libvlc_media_player_is_playing(m_player)){
        }

        libvlc_media_player_stop(m_player);
    }

}
