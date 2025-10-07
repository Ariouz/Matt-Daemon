#pragma once

#ifdef BONUS

# include <curl/curl.h>
# include <iostream>

# ifndef WEBHOOK_URL
# define WEBHOOK_URL "DEFINE AT COMPILE"
# endif

# include "TintinReporter.hpp"

class WebHookNotifier {

    private:
        WebHookNotifier();
        WebHookNotifier(const WebHookNotifier& other) = default;
        WebHookNotifier& operator=(const WebHookNotifier& other) = default;

    public:
        ~WebHookNotifier() = default;

        static WebHookNotifier& instance() {
            static WebHookNotifier _instance;
            return _instance;
        }

        static void send(const std::string& message);

};

#endif