#include "mlspch.h"
#include "mls/string.h"
#include "serializer.h"

namespace mls_internal {
		
	serializer::sr_extensions serializer::s_extensions;

	bool serializer::initialize(const std::string& file_path)
	{
		if (!mls::utilities::string::contains(file_path, ".ext")) {
			MLS_ERROR("Extension files must be in myfile.ext format");
			return false;
		}

		std::ifstream stream(file_path, std::ios::in);
		return parse<cereal::JSONInputArchive>(file_path, stream, s_extensions);
	}

	bool serializer::shutdown(const std::string& file_path)
	{
		if (!mls::utilities::string::contains(file_path, ".ext")) {
			MLS_ERROR("Extension files must be in myfile.ext format");
			return false;
		}

		std::ofstream stream(file_path, std::ios::out);
		return parse<cereal::JSONOutputArchive>(file_path, stream, s_extensions);
	}

	bool serializer::add_extension(const std::string& name, const extension& type) {
			
		const auto length = name.length();
		const auto ext = mls::utilities::string::remove_special_characters(name);

		if (ext.length() != length) { 
			MLS_WARN("No special characters allowed. Extension has been changed to:", ext);
		}

		if (ext.empty()) { 
			MLS_WARN("An extension name cannot be empty. Extension not created."); 
			return false;
		}

		if (!s_extensions.cache.try_emplace("." + ext, type).second) {
			MLS_ERROR("Extension already exists:", ext);
			return false;
		}

		s_extensions.filters.append(ext + ";");

		MLS_INFO("Extension created successfully:", ext);

		return true;
	}

	serializer::extension serializer::is_valid(const std::string& file_path)
	{
		auto token = file_path.find_last_of(".");
		if (token == std::string::npos) {
			MLS_ERROR("Invalid extension. Use format myfile.ext:", file_path);
			return extension::null;
		}

		const auto& name = file_path.substr(token);
		const auto& found = s_extensions.cache.find(name);

		if (found == s_extensions.cache.end()) {
			MLS_ERROR("Extension doesn't exist. Create it first:", name);
			return extension::null;
		}

		return found->second;
	}
}