#pragma once

#include "mls/core.h"
#include "mls/internal/log.h"
#include "mls/utilities.h"

namespace mls_internal {

	class serializer : private mls::no_copy {

		MLS_INTERNAL;

	public:
		enum class extension : unsigned int { null, bin, json, xml };

	private:
		struct sr_extensions {
			typedef std::map<std::string, extension> extension_cache;

			extension_cache cache;
			std::string filters;

		private:
			MLS_SERIALIZE(
				MLS_NVP(cache),
				MLS_NVP(filters));
		};

	public:
		serializer() = default;
		~serializer() = default;

	public:
		bool add_extension(const std::string& name, const extension& type);

		template <typename... Args>
		bool load(const std::string& file_path, Args&&... args);

		template <typename... Args>
		bool save(const std::string& file_path, Args&&... args);
		
	private:
		bool initialize(const std::string& extensions_file_path);
		bool shutdown(const std::string& extensions_file_path);
		extension is_valid(const std::string& file_path);

		template <typename ArchiveType, typename Stream, typename... Args>
		bool parse(const std::string& file_path, Stream& stream, Args&&... args);

	private:
		static sr_extensions s_extensions;
	};

	template <typename... Args>
	bool serializer::load(const std::string& file_path, Args&&... args) {
			
		if constexpr (sizeof...(Args) > 0) {

			const auto& extension = is_valid(file_path);
			if (!mls::utilities::types::enum_to_type(extension)) {
				return false;
			}

			if (extension == extension::bin) {
				std::ifstream stream(file_path, std::ios::binary);
				return parse<cereal::BinaryInputArchive>(file_path, stream, std::forward<Args>(args)...);
			}
			else {
				std::ifstream stream(file_path, std::ios::in);
				if (extension == extension::json) { 
					return parse<cereal::JSONInputArchive>(file_path, stream, std::forward<Args>(args)...);
				}
				else if (extension == extension::xml) { 
					return parse<cereal::XMLInputArchive>(file_path, stream, std::forward<Args>(args)...);
				}
			}
		}

		MLS_ERROR("Argument list empty when trying to load file:", file_path);

		return false;
	}


	template <typename... Args>
	bool serializer::save(const std::string& file_path, Args&&... args)
	{
		if constexpr (sizeof...(Args) > 0) {

			const auto& extension = is_valid(file_path);

			if (!utilities::types::enum_to_type(extension)) {
				return false;
			}

			if (extension == extension::bin) {
				std::ofstream stream(file_path, std::ios::binary);
				return parse<cereal::BinaryOutputArchive>(file_path, stream, std::forward<Args>(args)...);
			}
			else {
				std::ofstream stream(file_path, std::ios::out);
				if (extension == extension::json) {
					return parse<cereal::JSONOutputArchive>(file_path, stream, std::forward<Args>(args)...);
				}
				else if (extension == extension::xml) {
					return parse<cereal::XMLOutputArchive>(file_path, stream, std::forward<Args>(args)...);
				}
			}
		}

		MLS_ERROR("Argument list empty when trying to save file:", file_path);

		return false;
	}

	template <typename ArchiveType, typename Stream, typename... Args>
	bool serializer::parse(const std::string& file_path, Stream& stream, Args&&... args)
	{
		if (!stream || !stream.is_open() || !stream.good()) {
			MLS_ERROR("File path not found:", file_path);
			return false;
		}

		{
			ArchiveType archive(stream); archive(std::forward<Args>(args)...);
		}

		stream.close();

		MLS_INFO("File parsed successfully:", file_path);

		return true;
	}
}
/*!
	@brief
		Used to create a serializer object to save and load data.
*******************************************************************************************************************/
namespace mls {
	using serializer = mls_internal::serializer;
}