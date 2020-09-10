#pragma once
#ifndef _LFU_H
#define _LFU_H

#include <map>
#include <unordered_map>
#include <exception>

template <typename keytype, typename datatype> 
class lfu_cache
{
	std::unordered_map <keytype, datatype> datamap;
	std::multimap <int, keytype> freqmap;
	unsigned long hitcount = 0;
	unsigned long misscount = 0;
	unsigned long size = 0;

public:

	bool is_cached(const keytype key)
	{
		return datamap.find(key) != datamap.end();
	}

	class non_cached_exception : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "Requested key is not cached";
		}
	} nc_exc;

	datatype& get(const keytype key)
	{
		if (is_cached(key))
		{
			hitcount ++;
			return datamap[key];
		}
		else
		{
			misscount++;
			throw nc_exc;
		}
	}

	void put(const keytype key, const datatype data)
	{
		if (datamap.size() >= size)
		{
			int minfreq = freqmap.begin()->first;
			keytype rmkey = freqmap.find(minfreq)->second;
			freqmap.erase(minfreq);
			datamap.erase(rmkey);
		}
		std::pair <int, keytype> ins_pair = std::make_pair(1, key);
		freqmap.insert(ins_pair);
		datamap[key] = data;
	}

	void set_size(unsigned long _size)
	{
		size = _size;
	}

	unsigned long get_misscount()
	{
		return misscount;
	}

	unsigned long get_hitcount()
	{
		return hitcount;
	}
};

#endif //_LFU_H