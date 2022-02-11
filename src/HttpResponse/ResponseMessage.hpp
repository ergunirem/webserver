#ifndef RESPONSEMESSAGE_HPP
#define RESPONSEMESSAGE_HPP
#include <string>
#include <map>

namespace HTTPResponse {

    class ResponseMessage {

    public:
        ResponseMessage();
        ResponseMessage(const ResponseMessage& other);
        ~ResponseMessage();

    private:
        std::string _HTTP_version;
        std::string _status_code;
        std::string _reason_phrase;
        std::map<std::string, std::string> _request_headers;
        std::string _message_body;
    };
}

#endif
