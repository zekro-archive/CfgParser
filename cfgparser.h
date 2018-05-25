#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>


#define NULLINDEX 4294967295

class CfgParser {

	public:
		/**
		 *  @brief CfgParser class constructor
		 *  
		 *  @param [filename] Name and location of the config file 
		 *                    (defaultly) "./config.cfg"
		 */
		CfgParser(const std::wstring &filename = L"config.cfg");

		/**
		 *  @brief Load config file or create it, if not existent.
		 *
		 *  @param [createIfNotExistent] If true, a default config file will 
		 *                               be created with keys and values set
		 *                               with {@link setStandart} function.
		 *  @see {@link setStandart}
		 *  @returns True if loading was successful.
		 */
		bool load(const bool &createIfNotExistent = true);

		/**
		 *  @brief Create config file with default values set with {@link setStandart}
		 *         function at defined file location.
		 *         Attention: If you execute this function manually, this will overwrite
		 *         any existing config with the same name.
		 *
		 *  @see {@link setStandart}
		 *  @returns True if file creation was successful.
		 */
		bool create();

		/**
		 *  @brief 
		 */
		void setStandart(const std::map<std::wstring, std::wstring> &standartConf = std::map<std::wstring, std::wstring>());

		double getNumber(const std::wstring &key);
		std::wstring getString(const std::wstring &key);

		// <----  S O O N  ---->
		// template <typename T>
		// bool set(const std::wstring &key, const T &value);
		// 
		// template <typename T>
		// bool add(const std::wstring &key, const T &value = NULL);

	private:
		std::wstring                         m_filename;
		std::map<std::wstring, std::wstring> m_standartConf;
		std::map<std::wstring, long>         m_long_data;
		std::map<std::wstring, double>       m_double_data;
		std::map<std::wstring, std::wstring> m_string_data;
};