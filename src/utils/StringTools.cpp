//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#include "../core/Precompiled.hpp"

#include "../utils/StringTools.hpp"

using namespace utils;
using namespace std;

bool StringTools::IsDecimalNumber(const std::wstring & s) 
{ 
	return s != _T("E") && s != _T("e") && boost::all(s, boost::is_digit() || boost::is_any_of(_T(".,-,E,e"))); 
}

bool StringTools::IsIntegerNumber(const std::wstring & s) 
{ 
	if(!IsDecimalNumber(s))
		return false;

	uint pos = s.find(_T("."));
	if( pos == string::npos )
		return true;

	std::wstring s1 = s.substr(0, pos);
	std::wstring s2 = s.substr(pos+1);

	return (boost::all(s1, boost::is_digit()) && boost::all(s2, boost::is_any_of("0"))); 
}

bool StringTools::IsEmpty(const wstring& s)
{
  for(uint i = 0; i < s.size(); i++)
  {
    wchar_t c = s[i];
    if(c != ' ' && c != '\n' && c != '\t') return false;
  }
  return true;
}

wstring StringTools::ToUpper(const wstring& s)
{
	return 	boost::to_upper_copy(s);;
}

wstring StringTools::ToLower(const wstring& s)
{
	return boost::to_lower_copy(s);
}

bool StringTools::IsWhiteSpaceCharacter(wchar_t c)
{
    return (c == ' ')
        || (c == '\t')
        || (c == '\n')
        || (c == '\r')
        || (c == '\f');  
}

wstring StringTools::RemoveWhiteSpaces(const wstring & s)
{
  // Copy sequence
  wstring st (s);
  
  // For all sequence's characters
  for (uint i = 0; i < st.size(); i++)
  {
    if(IsWhiteSpaceCharacter(st[i]))
    {
      st.erase(st.begin() + i); // Remove character
      i--;
    }
  }

  // Send result
  return st;
}

wstring StringTools::RemoveFirstWhiteSpaces(const wstring & s)
{
  return 	boost::trim_left_copy(s);
}

wstring StringTools::RemoveLastWhiteSpaces(const wstring & s)
{
	return boost::trim_right_copy(s);;
}

wstring StringTools::RemoveSurroundingWhiteSpaces(const wstring & s)
{
	return boost::trim_copy(s);
}

void StringTools::ExtractPathAndFilename(const std::wstring& fullpath, std::wstring& path, std::wstring& filename)
{
	uint pos = fullpath.find_last_of(_T("/"));
	if(pos == std::wstring::npos)
	{
		pos = fullpath.find_last_of(_T("\\"));
		if(pos == std::wstring::npos)
			pos = -1;
	}

  std::wstring temp = fullpath.substr(pos+1);
	filename = temp;

	pos = fullpath.find_last_of(_T("/"));
	if(pos == std::wstring::npos)
	{
		pos = fullpath.find_last_of(_T("\\"));
		if(pos == std::wstring::npos)
			pos = 0;
	}

	temp = fullpath.substr(0,pos);
	path = temp;
}

wstring StringTools::ToString(int i)
{
	wostringstream oss;
  oss << i;
  return oss.str();
}

wstring StringTools::ToString(wchar_t c)
{
  wostringstream oss;
  oss << c;
  return oss.str();
}

wstring StringTools::ToString(float d, int precision, bool bScientific)
{
  wostringstream oss;
	if(bScientific)
		oss << scientific;
	else
		oss << fixed;

	oss << setprecision(precision) << d;
  return oss.str();
}

wstring StringTools::FormatNumberStr(const std::wstring &  s, int precision, bool bScientific)
{
	if(!IsDecimalNumber(s))
		return s;

	float f = ToFloat(s);
	return ToString(f, precision, bScientific);
}

int StringTools::ToInt(const wstring & s)
{
  wistringstream iss(s);
  int i;
  iss >> i;
  return i;
}

float StringTools::ToFloat(const wstring & s) 
{
  wistringstream iss(s);
  float d;
  iss >> d;
  return d;
}

double StringTools::ToDouble(const wstring & s) 
{
  wistringstream iss(s);
  double d;
  iss >> d;
  return d;
}


long StringTools::ToLong(const wstring & s) 
{
  wistringstream iss(s);
  long d;
  iss >> d;
  return d;
}

wstring StringTools::ResizeRight(const wstring & s, uint newSize, wchar_t fill) 
{
  if(s.size() > newSize) return s.substr(0, newSize);
  else return s + wstring(newSize - s.size(), fill);
}

wstring StringTools::ResizeLeft(const wstring & s, uint newSize, wchar_t fill)
{
  if(s.size() > newSize) return s.substr(s.size() - newSize);
  else return wstring(newSize - s.size(), fill) + s;
}

vector<wstring> StringTools::Split(const wstring & s, uint n)
{
  vector<wstring> v;
  wstring tmp = s;
  while(tmp.size() > n)
  {
    v.push_back(tmp.substr(0, n));
    tmp = tmp.substr(n);
  }
  v.push_back(tmp);
  return v;
}

wstring StringTools::RemoveSubstrings(const wstring & s, wchar_t blockBeginning, wchar_t blockEnding)
{
  wstring t = _T("");
  int blockCount = 0;
  int begPos = 0;
  for(uint i = 0; i < s.size(); i++)
  {
    wchar_t current = s[i];
    if(current == blockBeginning)
    {
      blockCount++;
      t += s.substr(begPos, i);
    }
    else if(current == blockEnding)
    {
      blockCount--;
      if(blockCount == 0) {
        begPos = i + 1;
      }
      else if(blockCount < 0)
			{
				blockCount = 0;
			}
    }
  }
  t += s.substr(begPos, s.npos);
  return t;
}

wstring StringTools::RemoveChar(const wstring & s, wchar_t c)
{
  // Copy sequence
  wstring st(s);

  // For all sequence's characters
  for (uint i = 0; i < st.size(); i++)
  {
    if (st[i] == c)
    {
      st.erase(st.begin() + i); // Remove character
      i--;
    }
  }

  // Send result
  return st;
}

wstring StringTools::ReplaceChar(const wstring & s, wchar_t c, wchar_t r)
{
  // Copy sequence
  wstring st(s);

  // For all sequence's characters
  for (uint i = 0; i < st.size(); i++)
  {
    if (st[i] == c)
    {
      st[i] = r; // replace character
    }
  }

  // Send result
  return st;
}

uint StringTools::Count(const wstring & s, const wstring & pattern)
{
  uint count = 0;
  string::size_type index = s.find(pattern);
  while(index != string::npos)
  {
    count++;
    index = s.find(pattern, index+1);
  }
  return count;
}

