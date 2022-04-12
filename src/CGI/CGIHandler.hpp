#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <exception>

#include "../HTTPRequest/RequestMessage.hpp"
#include "../HTTPResponse/SpecifiedConfig.hpp"

class CGIHandler
{
private:
	char *_envp[21];				// TODO check if this is the right size, terminated with 0
	char *_argument[2];
	std::map<std::string, std::string> _meta_variables;
	std::string _cgi_name;
	std::vector<std::string> _cgi_extention;
	bool _search_cgi_extension;
	void update_path_translated(void);
	int _input_pipe[2];
	int _output_pipe[2];
	std::string _response;
	class CGIexception: public std::exception{
		const char* what() const _NOEXCEPT { return "internal server error"; }
	};

public:		
	CGIHandler();
	~CGIHandler();
	void parse_meta_variables(HTTPRequest::RequestMessage *_http_request_message, HTTPResponse::SpecifiedConfig &_config);
	void search_cgi(std::vector<std::string> &path);
	void set_envp(void);
	void set_argument(std::string cgi_name);
	void set_response_message_body(std::string str);
	std::string get_response_message_body();
	bool get_search_cgi_extention();
	int get_read_fd() const;
	int get_write_fd() const;
	void execute_cgi(HTTPRequest::RequestMessage *_http_request_message, HTTPResponse::SpecifiedConfig &_config, int kq);
};
