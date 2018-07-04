#pragma once
#ifdef _UNICODE
#define _tregex std::wregex
#define _string std::wstring
#define _smatch std::wsmatch
#else
#define _tregex std::regex
#define _string std::string
#define _smatch std::smatch

#endif
enum REGEX_POLICY {
	ICASE = 0,
	ECMA,
	ECMA_ICASE
};
namespace Util
{
	template<REGEX_POLICY N = ECMA_ICASE> bool IsMatchRegex(const TCHAR* target, const TCHAR* regrex)
	{
		const std::regex_constants::syntax_option_type PolicyRegrex[] =
		{
			std::regex_constants::icase,
			std::regex_constants::ECMAScript,
			std::regex_constants::icase | std::regex_constants::ECMAScript
		};
		_tregex self_regex(regrex, PolicyRegrex[N]);
		return std::regex_match(target, self_regex);
	}

	template<REGEX_POLICY N = ECMA_ICASE> const TCHAR* RegexReplace(const TCHAR* target, const TCHAR* regrex)
	{
		static _string s;
		s.clear();
		const std::regex_constants::syntax_option_type PolicyRegrex[] =
		{
			std::regex_constants::icase,
			std::regex_constants::ECMAScript,
			std::regex_constants::icase | std::regex_constants::ECMAScript
		};
		_tregex self_regex(regrex, PolicyRegrex[N]);
		s = std::regex_replace(target, self_regex, _T(""));
		return s.c_str();
	}

}