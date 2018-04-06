#ifndef VLC_CLIENT_H
#define VLC_CLIENT_H


#include <vlc/vlc.h>
#include <string>


namespace Client {

    class VLC {


        public:

            VLC(const std::string& file_path , int count = 1);
            virtual ~VLC();

            void run();

        private:


            int m_count; // how many times we want to play the media file.
            libvlc_instance_t* m_instance;
            libvlc_media_t* m_media_file;
            libvlc_media_player_t* m_player;

            void init_instance();
            void load_file(const std::string& file_path);
            static libvlc_event_manager_t* m_event_manager;

            static void player_position_callback(const libvlc_event_t* event , void* params);

            void play();
            void attach_event();

    };
};

#endif
