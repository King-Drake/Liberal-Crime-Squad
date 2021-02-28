class LootTypePool : ItemTypePool {
private:
	static bool lootTypePoolInitiated;
public:
	static LootTypePool getInstance();
	const int lenpool() const;
	const string getIdName(int i);
	void delete_and_clear_pool();
	const string getName(const string& str);
};