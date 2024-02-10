#include "YTEngine/Tools/Stringf.h"

namespace Yor
{
  std::unordered_map<std::string, uint64_t> Stringf::s_hashedStrings;

  std::vector<std::string> Stringf::splitBy(const std::string& str, const char delim)
  {
		std::vector<std::string> lines;
		std::string current = "";

		for (size_t i = 0; i < str.size(); i++)
		{
			if (str[i] == delim)
			{
				if (!current.empty())
				{
					lines.push_back(current);
					current = "";
				}

				continue;
			}

			current += str[i];
		}

		if (!current.empty())
			lines.push_back(current);

		return lines;
  }

  uint64_t Stringf::hash(const std::string& data)
  {
    if (s_hashedStrings.contains(data)) return s_hashedStrings[data];

    uint64_t h = hash(data.c_str());
    s_hashedStrings[data] = h;

    return h;
  }
}