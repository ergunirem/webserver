#pragma once

#include <string>
#include <map>

namespace HTTPResponse {
    class ResponseMessage {

    private:
        std::string _HTTP_version;
        std::string _status_code;
        std::string _reason_phrase;
		std::string _status_line;
        std::string _message_body;
        std::string _complete_response;
		std::map<std::string, std::string> _response_headers;

    public:
        ResponseMessage();
        ResponseMessage(const ResponseMessage& other);
        ~ResponseMessage();

        void set_status_code(const std::string& code);
        void set_reason_phrase(const std::string& reason);
		void set_status_line(const std::string& line);
        void set_message_body(const std::string& body);
        void set_complete_response(const std::string& response);
        void append_complete_response(const std::string& response_part);
		void set_header_element(std::pair<std::string, std::string>& header_field);
        const std::string& get_HTTP_version() const;
        const std::string& get_status_code() const;
        const std::string& get_reason_phrase() const;
		const std::string& get_status_line() const;
        const std::string& get_message_body() const;
        const std::string& get_complete_response() const;
		const std::map<std::string, std::string>& get_response_headers() const;
    };
}
