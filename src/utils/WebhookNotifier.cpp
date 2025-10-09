#include "WebHookNotifier.hpp"

#ifdef BONUS

WebHookNotifier::WebHookNotifier() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

void WebHookNotifier::send(const std::string& message) {
    CURL* curl = curl_easy_init();
    if (!curl)
        return;

    curl_easy_setopt(curl, CURLOPT_URL, WEBHOOK_URL);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message.c_str());

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
        Tintin_reporter::error("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));

    curl_easy_cleanup(curl);
}

#endif
