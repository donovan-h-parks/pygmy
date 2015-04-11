//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _TEXTSEARCH_H_
#define _TEXTSEARCH_H_

#include "../core/Precompiled.hpp"

#include "../core/NodePhylo.hpp"
#include "../core/Filter.hpp"

#include "../utils/StringTools.hpp"

namespace pygmy
{

/**
 * @brief Search a list of words. Functionality is provided to
 *				filter the list of words based on prefix. The node assoicated
 *				with a word is stored for later retrieval.
 */
class TextSearch
{
public:
	/** Constructor. */
	TextSearch(): m_dataFilter(new Filter()) {}

	/** Clear the list of words. */
	void Clear() { m_words.clear(); }

	/**
	 * @brief Add a word to the list.
	 * @param word Word to add to the list.
	 * @param id Node id to associate with the given word.
	 */
	void Add(const std::wstring& word, uint id) { m_words.insert(std::pair<std::wstring, uint>(word, id)); }

	/**
	 * @brief Get a vector of all words which match the specified search.
	 *				A filter of "" will return the entire list of words.
	 * @param searchStr String to search for.
	 * @param searchType Type of search to perform (i.e., starts with, contains, ends with, matches)
	 */
	std::vector<std::wstring>& FilterData(const std::wstring& searchStr, const std::wstring& searchType)
	{
		m_wordFilter.clear();
		m_dataFilter->Clear();

		std::wstring searchLower = utils::StringTools::ToLower(searchStr);

		// Add in all text that match the specified search.
		std::map<std::wstring, uint>::iterator it;
		for (it = m_words.begin() ; it != m_words.end(); ++it)
		{
			std::wstring strLower = utils::StringTools::ToLower(it->first);

			bool match = true;

			if(searchType == _T("matches"))
			{
				if(searchLower.size() != strLower.size())
				{
					match = false;
				}
				else
				{
					uint pos = strLower.find(searchLower);
					if(pos != 0)
						match = false;
				}
			}
			else if(searchType == _T("starts with"))
			{
				uint pos = strLower.find(searchLower);
				if(pos != 0)
					match = false;
			}
			else if(searchType == _T("ends with"))
			{
				for(uint j = 0; j < strLower.size(); ++j)
				{
					if(searchLower[searchLower.size()-j-1] != strLower[strLower.size()-j-1])
					{
						match = false;
						break;
					}
				}
			}
			else if(searchType == _T("contains"))
			{
				if(strLower.find(searchLower) == std::wstring::npos)
					match = false;
			}

			if(match)
			{
				m_wordFilter.push_back(it->first);
				
				if(searchLower != _T(""))
					m_dataFilter->Add(it->second);
			}
		}

		return m_wordFilter;		
	}

	/**
	 * @brief Get data associated with a given word.
	 * @param word Word to retrieve data for.
	 * @param id Id associated with the given word.
	 * @return True if the word was found, else false.
	 */
	bool Data(const std::wstring& word, uint& id)
	{ 
		std::map<std::wstring, uint>::iterator it;
		
		it = m_words.find(word);
		if(it != m_words.end())
		{
			id = it->second;
			return true;
		}

		return false; 
	}

	/**
	 * @brief Get data for filtered items.
	 * @return Filter containing data only for filtered items.
	 */
	FilterPtr DataFilter() { return m_dataFilter; }

private:
	/** Map words to associated data. */
	std::map<std::wstring, uint> m_words;

	/** List of filtered words. */
	std::vector<std::wstring> m_wordFilter;

	/** Filtered data items. */
	FilterPtr m_dataFilter;
};

}


#endif

