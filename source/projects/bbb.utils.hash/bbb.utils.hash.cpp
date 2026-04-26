#include "c74_min.h"

#include <CommonCrypto/CommonDigest.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class bbb_utils_hash : public c74::min::object<bbb_utils_hash> {
public:
	MIN_DESCRIPTION{"Compute SHA-256 and MD5 hashes"};
	MIN_TAGS{"hash, sha256, md5, utility"};
	MIN_AUTHOR{"2bit"};

	c74::min::inlet<> input{this, "(anything) hash messages"};
	c74::min::outlet<> output{this, "(symbol) hex digest"};

	c74::min::message<> sha256_msg{this, "sha256", "Compute SHA-256 hash of text",
		MIN_FUNCTION {
			auto text = atoms_to_string(args);
			auto digest = sha256(text);
			output.send(c74::min::symbol(digest));
			return {};
		}};

	c74::min::message<> md5_msg{this, "md5", "Compute MD5 hash of text",
		MIN_FUNCTION {
			auto text = atoms_to_string(args);
			auto digest = md5(text);
			output.send(c74::min::symbol(digest));
			return {};
		}};

	c74::min::message<> sha256_file_msg{this, "sha256_file", "Compute SHA-256 hash of file",
		MIN_FUNCTION {
			auto path = atoms_to_string(args);
			auto data = read_file(path);
			if(data.empty() && !file_exists(path)) {
				cerr << "file not found: " << path << c74::min::endl;
				return {};
			}
			auto digest = sha256(data);
			output.send(c74::min::symbol(digest));
			return {};
		}};

	c74::min::message<> md5_file_msg{this, "md5_file", "Compute MD5 hash of file",
		MIN_FUNCTION {
			auto path = atoms_to_string(args);
			auto data = read_file(path);
			if(data.empty() && !file_exists(path)) {
				cerr << "file not found: " << path << c74::min::endl;
				return {};
			}
			auto digest = md5(data);
			output.send(c74::min::symbol(digest));
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

	static auto to_hex(const uint8_t *data, size_t len) -> std::string {
		static const char hex[] = "0123456789abcdef";
		std::string result;
		result.reserve(len * 2);
		for(size_t i = 0; i < len; ++i) {
			result += hex[data[i] >> 4];
			result += hex[data[i] & 0x0F];
		}
		return result;
	}

	static auto sha256(const std::string &input) -> std::string {
		uint8_t digest[CC_SHA256_DIGEST_LENGTH];
		CC_SHA256(input.data(), static_cast<CC_LONG>(input.size()), digest);
		return to_hex(digest, CC_SHA256_DIGEST_LENGTH);
	}

	static auto md5(const std::string &input) -> std::string {
		uint8_t digest[CC_MD5_DIGEST_LENGTH];
		CC_MD5(input.data(), static_cast<CC_LONG>(input.size()), digest);
		return to_hex(digest, CC_MD5_DIGEST_LENGTH);
	}

	static auto read_file(const std::string &path) -> std::string {
		std::ifstream ifs(path, std::ios::binary);
		if(!ifs) return "";
		std::ostringstream ss;
		ss << ifs.rdbuf();
		return ss.str();
	}

	static auto file_exists(const std::string &path) -> bool {
		std::ifstream ifs(path);
		return ifs.good();
	}
};

MIN_EXTERNAL(bbb_utils_hash);
