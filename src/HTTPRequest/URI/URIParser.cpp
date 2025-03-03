#include "URIParser.hpp"

#include <ctype.h>

#include "../../Utility/Utility.hpp"
#include "../../HTTP/Exceptions/RequestException.hpp"

namespace HTTPRequest {

	URIParser::URIParser(std::string URI_input)
	{
		this->URI_input = URI_input;
	}

	URIParser::~URIParser(){}

	static int hex_to_dec(char a)
	{
		int dec_value;
		if(isalpha(a))
		{
			a = std::toupper(a);
			if(a <= 'F' && a >= 'A')
				dec_value = static_cast<int>(a) - 55;
			else
				dec_value = -1;
		}
		else if(isdigit(a))
			dec_value = a - 48;
		else
			dec_value = -1;
		return dec_value;
	}

	void URIParser::pct_decoding(std::string &target)
	{
		int len = target.length();
		int decimal_value;
		std::string temp = target;
		target.erase(0, len);
		for(int i = 0; i < len; i++)
		{
			if(temp[i] == '%' && len > i + 2)
			{
				int first_dec = hex_to_dec(temp[i + 1]);
				int second_dec = hex_to_dec(temp[i + 2]);
				if(first_dec != -1 && second_dec != -1)
				{
					decimal_value = first_dec * 16 + second_dec;
					target += static_cast<char>(decimal_value);
					i += 2;
				}
				else
					throw Exception::RequestException(HTTPResponse::BadRequest);//the write error code to throw in case the provided %hh is not qualified for decoding
			}
			else if(temp[i] == '%' && len <= (i + 2))
				throw Exception::RequestException(HTTPResponse::BadRequest);//the write error code to throw in case the provided %hh is not complete
			else
				target += temp[i];
		}
	}


	void URIParser::parse(URIData &uri)
	{
		if (URI_input.size() > 2000)
			throw Exception::RequestException(HTTPResponse::URITooLong);
		parse_path(uri);
		parse_queries(uri);
	}

	void URIParser::parse_path(URIData &uri)
	{
		std::string line;
		std::vector<std::string> path;
		size_t len = URI_input.length();
		/*if the path is empty, it should have "/" at least*/
		if(len == 0)
		{
			path.push_back("/");
			uri.set_path(path);
			return;
		}
		size_t delimiter_query_position = URI_input.find_first_of("?");
		if(delimiter_query_position != std::string::npos)
		{
			query_string = URI_input.substr(delimiter_query_position + 1, len - delimiter_query_position - 1);
			URI_input.erase(delimiter_query_position, len - delimiter_query_position);
		}
		while(URI_input.length() > 0)
		{
			size_t delimiter_slash_position = URI_input.find_first_of("/");
			if(delimiter_slash_position == std::string::npos)
			{
				len = URI_input.length();
				line = URI_input.substr(0, len);
				pct_decoding(line);
				path.push_back(line);
				URI_input.erase(0, len);
			}
			else
			{
				line = URI_input.substr(0, delimiter_slash_position);
				pct_decoding(line);
				path.push_back(line);
				URI_input.erase(0, delimiter_slash_position + 1);
			}
		}
		uri.set_path(path);
	}

	void URIParser::parse_queries(URIData &uri)
	{
		pct_decoding(query_string);
		uri.set_query(query_string);
	}
}
