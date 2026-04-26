#include "c74_min.h"

#include <cstdint>
#include <cstdio>
#include <string>

class bbb_utils_base64 : public c74::min::object<bbb_utils_base64> {
public:
	MIN_DESCRIPTION{"Base64 encode and decode"};
	MIN_TAGS{"base64, encode, decode, utility"};
	MIN_AUTHOR{"2bit"};

	c74::min::inlet<> input{this, "(anything) encode/decode messages"};
	c74::min::outlet<> output{this, "(symbol) result"};

	c74::min::message<> encode_msg{this, "encode", "Base64 encode text",
		MIN_FUNCTION {
			auto text = atoms_to_string(args);
			auto result = base64_encode(
				reinterpret_cast<const uint8_t *>(text.data()), text.size());
			output.send(c74::min::symbol(result));
			return {};
		}};

	c74::min::message<> decode_msg{this, "decode", "Base64 decode text",
		MIN_FUNCTION {
			auto text = atoms_to_string(args);
			auto result = base64_decode(text);
			output.send(c74::min::symbol(result));
			return {};
		}};

private:
	static auto atoms_to_string(const c74::min::atoms &args) -> std::string {
		std::string result;
		for(size_t i = 0; i < args.size(); ++i) {
			if(i > 0) result += " ";
			result += std::string(args[i]);
		}
		return result;
	}

	static auto base64_encode(const uint8_t *data, size_t len) -> std::string {
		static const char table[] =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		std::string result;
		result.reserve((len + 2) / 3 * 4);

		for(size_t i = 0; i < len; i += 3) {
			uint32_t n = static_cast<uint32_t>(data[i]) << 16;
			if(i + 1 < len) n |= static_cast<uint32_t>(data[i + 1]) << 8;
			if(i + 2 < len) n |= static_cast<uint32_t>(data[i + 2]);

			result += table[(n >> 18) & 0x3F];
			result += table[(n >> 12) & 0x3F];
			result += (i + 1 < len) ? table[(n >> 6) & 0x3F] : '=';
			result += (i + 2 < len) ? table[n & 0x3F] : '=';
		}
		return result;
	}

	static auto base64_decode(const std::string &input) -> std::string {
		static const int8_t lookup[256] = {
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,63,
			52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-1,-1,-1,
			-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
			15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,
			-1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
			41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		};

		std::string result;
		result.reserve(input.size() * 3 / 4);

		uint32_t buf = 0;
		int bits = 0;
		for(auto c : input) {
			if(c == '=') break;
			auto val = lookup[static_cast<uint8_t>(c)];
			if(val < 0) continue;
			buf = (buf << 6) | static_cast<uint32_t>(val);
			bits += 6;
			if(bits >= 8) {
				bits -= 8;
				result += static_cast<char>((buf >> bits) & 0xFF);
			}
		}
		return result;
	}
};

MIN_EXTERNAL(bbb_utils_base64);
