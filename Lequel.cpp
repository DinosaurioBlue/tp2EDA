/**
 * @brief Lequel? language identification based on trigrams
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 *
 * @cite https://towardsdatascience.com/understanding-cosine-similarity-and-its-application-fd42f585296a
 */

#include <cmath>
#include <codecvt>
#include <locale>
#include <iostream>

#include "Lequel.h"

using namespace std;

/**
 * @brief Builds a trigram profile from a given text.
 *
 * @param text Vector of lines (Text)
 * @return TrigramProfile The trigram profile
 */
TrigramProfile buildTrigramProfile(const Text &text)
{
    wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    // Your code goes here...
    TrigramProfile TrigMap= TrigramProfile();
    for (auto line : text){
        if ((line.length() > 0) && (line[line.length() - 1] == '\r'))
            line = line.substr(0, line.length() - 1);
            
             wstring unicodeString = converter.from_bytes(line);

             if (unicodeString.length() <= 3)
        {
            continue;
        }
            
            for(int i = 0; i<unicodeString.length()-2;++i){
                wstring temp_wstring = unicodeString.substr(i,3);//cuts the strings in 3 letters

                TrigMap[converter.to_bytes(temp_wstring)]++;
                /*It creates a key for each trigram, and increments its value if found*/
            }
           

    }
    normalizeTrigramProfile(TrigMap);

    return TrigMap;
}

/**
 * @brief Normalizes a trigram profile.
 *
 * @param trigramProfile The trigram profile.
 */
void normalizeTrigramProfile(TrigramProfile &trigramProfile)
{   float temp_sum, temp_sqr;
    temp_sqr = temp_sum = 0.0F;
    for(auto &it : trigramProfile){//iterating each key
        temp_sqr = (it.second*it.second);
        temp_sum += temp_sqr;
    }  
    temp_sum= sqrt(temp_sum);//norm of the vector 
    for(auto &it : trigramProfile){//iterating each key
        it.second /= temp_sum;//normalizing each vector 
    }  


    return;
}

/**
 * @brief Calculates the cosine similarity between two trigram profiles
 *
 * @param textProfile The text trigram profile
 * @param languageProfile The language trigram profile
 * @return float The cosine similarity score
 */
float getCosineSimilarity(TrigramProfile &textProfile, TrigramProfile &languageProfile)
{
    float cos_sim;
    for(auto &element : textProfile ){
        auto temp = languageProfile.find(element.first);
        if(temp != languageProfile.end()){
            cos_sim+=(temp->second * element.second); 
        }
    }
    return cos_sim;
}

/**
 * @brief Identifies the language of a text.
 *
 * @param text A Text (vector of lines)
 * @param languages A list of Language objects
 * @return string The language code of the most likely language
 */
string identifyLanguage(const Text &text, LanguageProfiles &languages)
{
    

    return ""; // Fill-in result here
}
