#include "cfgparser.h"

// HELP FUNCTIONS ---------------------------------------------

std::wstring trim(const std::wstring &inpt) {
	std::wstring out(inpt);
	while (out.at(0) == L' ')
		out = out.substr(1, out.length());
	while (out.at(out.length() - 1) == L' ')
		out = out.substr(0, out.length() - 1);
	return out;
}

long toLong(const std::wstring &root) {
	long out = NULL;
	if (root.find(L'.') == NULLINDEX) {
		try {
			out = std::stol(root);
		}
		catch (const std::exception &e) {}
	}
	return out;
}

double toDouble(const std::wstring &root) {
	double out = NULL;
	try {
		out = std::stod(root);
	}
	catch (const std::exception &e) {}
	return out;
}


// CLASS MEMBERS ----------------------------------------------

CfgParser::CfgParser(const std::wstring &filename) {
	m_filename = filename;
}

bool CfgParser::load(const bool &createIfNotExistent)
{
	std::wifstream fs(m_filename);
	if (!fs.good())
		if (createIfNotExistent)
			create();
		else
			return false;

	for (std::wstring line; std::getline(fs, line); ) {
		int commentAt = line.find(L';');
		if (commentAt == 0)
			continue;
		else
			line = line.substr(0, commentAt);

		int splitter = line.find(L'=');
		std::wstring key = trim(line.substr(0, splitter)),
					 val = trim(line.substr(splitter + 1, line.length() - splitter - 1));

		long _t_l = toLong(val);
		if (_t_l != NULL) {
			m_long_data[key] = _t_l;
			continue;
		}

		double _t_d = toDouble(val);
		if (_t_d != NULL) {
			m_double_data[key] = _t_d;
			continue;
		}

		m_string_data[key] = val;
	}

	return true;
}

bool CfgParser::create()
{
	std::wofstream fs(m_filename);
	if (fs.good()) {
		for (auto it = m_standartConf.begin(); it != m_standartConf.end(); it++) {
			fs << it->first << " = " << it->second << std::endl;
		}
		fs.close();
		return true;
	}
	return false;
}

void CfgParser::setStandart(const std::map<std::wstring, std::wstring>& standartConf) {
	m_standartConf = standartConf;
}

double CfgParser::getNumber(const std::wstring &key) {
	if (m_long_data.count(key))
		return m_long_data[key];
	else return m_double_data[key];
}

std::wstring CfgParser::getString(const std::wstring &key) {
	return m_string_data[key];
}
