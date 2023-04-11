#pragma once

struct ItemData
{
	UINT key;
	string name;
	UINT price;
	wstring fileName;
};

class DataManager : public Singleton<DataManager>
{
public:
	DataManager();
	~DataManager();

	map<UINT, ItemData> GetItemDatas() { return itemDatas; }
private:
	void LoadItemTable();

private:
	map<UINT, ItemData> itemDatas;
};