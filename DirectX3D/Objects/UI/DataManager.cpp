#include "Framework.h"

DataManager::DataManager()
{
	LoadItemTable();
}

DataManager::~DataManager()
{
}

void DataManager::LoadItemTable()
{
	FILE* file;
	fopen_s(&file, "DataTables/ItemTable.csv", "r");

    bool isFirstLine = true;

    while (true)
    {
        char temp[1024];
        fgets(temp, 1024, file);

        if (isFirstLine)
        {
            isFirstLine = false;
            continue;
        }

        if (feof(file))
            return;

        string str = temp;
        Replace(str, "\n", "");

        vector<string> table = SplitString(str, ",");

        ItemData data;

        data.key = stoi(table[0]);
        data.name = table[1];
        data.price = stoi(table[2]);      
        data.fileName = ToWString(table[3]);

        itemDatas[data.key] = data;
    }
}
