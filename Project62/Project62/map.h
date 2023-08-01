#pragma once
#include "RBTree.h"
namespace dianxia
{
	template<class K,class V>
	class map
	{
		struct MapKeyoft
		{
			const K& operator()(const pair<const K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename RBTree <K, pair<const K, V>, MapKeyoft>::iterator iterator;
		
		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}
		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = _t.Insert(make_pair(key, V()));
			return ret.first->second;
		}

	private:
		RBTree<K, pair<const K, V>, MapKeyoft> _t;
	};
	
}