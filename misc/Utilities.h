#if !defined(L1_UTILITIES_H)

#define L1_UTILITIES_H

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

#include "./Types.h"

namespace misc {
    std::vector<std::string> Split (std::string D_String, std::string D_Delimiter) {
        ::size_t
            D_Start = 0,
            D_Finish,
            D_DelimiterLingth = D_Delimiter.size();

        std::string D_Token;
        std::vector<std::string> D_Result;

        while ((D_Finish = D_String.find(D_Delimiter, D_Start)) != std::string::npos) {
            D_Token = D_String.substr(D_Start, D_Finish - D_Start);
            D_Start = D_Finish + D_DelimiterLingth;
            D_Result.push_back(D_Token);
        }

        D_Result.push_back(D_String.substr(D_Start));
        return D_Result;
    }

    template<typename T>
    std::vector<T> Delete (std::vector<T> D_Vector, ::size_t D_Index) {
        std::vector<T> D_NewVector;

        for (::size_t D_Iterator = 0; D_Iterator < D_Vector.size(); D_Iterator++) {
            if (D_Iterator != D_Index) {
                D_NewVector.push_back(D_Vector.at(D_Iterator));
            }
        }

        return D_NewVector;
    }

    std::vector<std::string> Cut (std::vector<std::string> D_Vector, ::size_t D_Start, ::size_t D_Finish) {
        std::vector<std::string> D_Result;

        for (::size_t D_Iterator = D_Start; D_Iterator < D_Finish; D_Iterator++) {
            D_Result.push_back(D_Vector.at(D_Iterator));
        }

        return D_Result;
    }

    bool Has (std::vector<std::string> D_Vector, std::string D_Element) {
        for (std::string D_Item : D_Vector) {
            if (D_Item.compare(D_Element) == 0) {
                return true;
            }
        }

        return false;
    }

    std::string Trim (const std::string& S_String,const std::string& S_WhiteSpaceTemplate = " \t")
    {
        const auto strBegin = S_String.find_first_not_of(S_WhiteSpaceTemplate);
        if (strBegin == std::string::npos)
            return "";

        const auto strEnd = S_String.find_last_not_of(S_WhiteSpaceTemplate);
        const auto strRange = strEnd - strBegin + 1;

        return S_String.substr(strBegin, strRange);
    }

    std::string Reduce (const std::string& S_String, const std::string& fill = " ", const std::string& S_WhiteSpaceTemplate = " \t")
    {
        auto result = Trim(S_String, S_WhiteSpaceTemplate);

        auto beginSpace = result.find_first_of(S_WhiteSpaceTemplate);
        while (beginSpace != std::string::npos)
        {
            const auto endSpace = result.find_first_not_of(S_WhiteSpaceTemplate, beginSpace);
            const auto range = endSpace - beginSpace;

            result.replace(beginSpace, range, fill);

            const auto newStart = beginSpace + fill.length();
            beginSpace = result.find_first_of(S_WhiteSpaceTemplate, newStart);
        }

        return result;
    }

    bool IsNumber (const std::string& S_String)
    {
        return !S_String.empty() && std::find_if(S_String.begin(), S_String.end(), [](unsigned char c) { return !std::isdigit(c); }) == S_String.end();
    }
}

#endif