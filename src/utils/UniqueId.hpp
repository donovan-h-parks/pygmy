//=======================================================================
// Copyright 2008, Dalhousie University
// Author: Donovan Parks
//
// The contents of this file are licensed under the 
// Attribution-ShareAlike Creative Commons License:
// http://creativecommons.org/licenses/by-sa/3.0/
//=======================================================================

#ifndef _UNIQUE_ID_
#define _UNIQUE_ID_

#include "../core/Precompiled.hpp"

namespace utils
{

/**
 * @brief Singleton class for generating unique id's.
 */
class UniqueId
{
public:
	/** Specific unique ID flags. */ 
	enum ID_FLAGS { NO_ID = 0 }; 

public:
	/** Destructor */
	~UniqueId() { }

	/** Get the one and only instance of the state class. */
	static UniqueId& Inst()
	{
		static UniqueId uniqueId;
		return uniqueId;
	}

	/** Get unique id. */
	uint GenerateId() 
	{ 
		return m_uniqueId++;
	}

protected:
	/** Private singleton constructor (must instantiate  this class through Inst()). */
	UniqueId(): m_uniqueId(1) {}

	/** Private copy constructor (must instantiate  this class through Inst()). */
  UniqueId(const UniqueId&);

	/** Private assignment constructor (must instantiate  this class through Inst()). */
  UniqueId& operator= (const UniqueId&);


private:
	/** Unique number. */
	uint m_uniqueId;
	
};

}

#endif
