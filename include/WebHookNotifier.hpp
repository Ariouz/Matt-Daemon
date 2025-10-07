#pragma once

#ifdef BONUS

# include <curl/curl.h>
# include <iostream>

# ifndef WEBHOOK_URL
# define WEBHOOK_URL "https://webhook.site/cfbaccb6-8991-46d4-ab92-b9a309fa1fe4"
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