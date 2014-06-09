#include "../core/string.h"
#include <string>
#include <vector>

using namespace std;

class IniNode {
public:
    IniNode(const string& key, const string& value) : key(key), value(value) {}
    const string& GetKey() const { return key; }
    const string& GetValue() const { return value; }
private:
    string key;
    string value;
};

class IniSection {
public:
    IniSection(const string& name) : name(name) {}
    const string& GetName() const { return name; }
    int CountNodes() const { return nodes.size(); }
    const IniNode* GetNode(int i) const { return &nodes[i]; }
    IniNode* GetNode(int i) { return &nodes[i]; }
    const IniNode* FindNode(const string& key) const {
        for ( int i = 0; i < nodes.size(); i++ ) {
            if ( nodes[i].GetKey() == key ) return &nodes[i];
        }
    }
    IniNode* FindNode(const string& key) {
        for ( int i = 0; i < nodes.size(); i++ ) {
            if ( nodes[i].GetKey() == key ) return &nodes[i];
        }
    }
    void AddNode(const IniNode& node) {
        nodes.push_back(node);
    }
private:
    string name;
    vector<IniNode> nodes;
};

class IniFile {
public:
    IniFile(const string& path) : rootSection("<root>") {
        IniSection section("");
        vector<string>* lines = SplitString(Replace(Replace(LoadString(path), "\r\n", "\n"), "\r", "\n"), "\n");
        for ( vector<string>::iterator it = lines->begin(); it != lines->end(); it++ ) {
            // Remove leading and trailing blanks
            string line = Trim(*it);
            
            // Skip empty lines
            if ( line == "" ) continue;
            
            // Skip comments
            if ( line[0] == '#' || line[0] == ';' ) continue;
            
            // Check if we are opening a new section
            if ( line[0] == '[' ) {
                AddSection(section);
                section = IniSection(line);
            } else {
                // Parse node
                vector<string>* arr = SplitString(line, "=");
                if ( arr->size() != 2 ) continue;
                IniNode node(Trim(), Trim());
                FreeArray(arr);
            }
        }
        FreeArray(lines);
    }
private:
    IniSection rootSection;
    vector<IniSection> sections;
};