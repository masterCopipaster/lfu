
#include <stdio.h>
#include <iostream>
#include <string>
#include "lfu.h"

lfu_cache <int, std::string> cache;
int main()
{
	cache.set_size(3);
	cache.put(1, "string 1");
	cache.put(2, "string 2");
	cache.put(3, "string 3");
	cache.put(4, "string 4");
	cache.put(5, "string 5");
	std::cout << cache.get(4) << std::endl;
	return 0;
}