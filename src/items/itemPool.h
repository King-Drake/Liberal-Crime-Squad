#pragma once
class ItemTypePool {
public:
	virtual const int lenpool() const = 0;
	virtual void delete_and_clear_pool() = 0;
};
