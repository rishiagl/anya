//this file is generated by program(drogon_ctl) automatically,don't modify it!
#include "model_h.h"
#include <drogon/utils/OStringStream.h>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <list>
#include <deque>
#include <queue>
#include "create_model.h"
using namespace drogon_ctl;

using namespace drogon;
std::string model_h::genText(const DrTemplateData& model_h_view_data)
{
	drogon::OStringStream model_h_tmp_stream;
	std::string layoutName{""};
	model_h_tmp_stream << "/**\n";
	model_h_tmp_stream << " *\n";
	model_h_tmp_stream << " *  ";
{
    auto & val=model_h_view_data["className"];
    if(val.type()==typeid(const char *)){
        model_h_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        model_h_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
	model_h_tmp_stream << ".h\n";
	model_h_tmp_stream << " *  DO NOT EDIT. This file is generated by drogon_ctl\n";
	model_h_tmp_stream << " *\n";
	model_h_tmp_stream << " */\n";
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "#pragma once\n";
	model_h_tmp_stream << "#include <drogon/orm/Result.h>\n";
	model_h_tmp_stream << "#include <drogon/orm/Row.h>\n";
	model_h_tmp_stream << "#include <drogon/orm/Field.h>\n";
	model_h_tmp_stream << "#include <drogon/orm/SqlBinder.h>\n";
	model_h_tmp_stream << "#include <drogon/orm/Mapper.h>\n";
	model_h_tmp_stream << "#ifdef __cpp_impl_coroutine\n";
	model_h_tmp_stream << "#include <drogon/orm/CoroMapper.h>\n";
	model_h_tmp_stream << "#endif\n";
	model_h_tmp_stream << "#include <trantor/utils/Date.h>\n";
	model_h_tmp_stream << "#include <trantor/utils/Logger.h>\n";
	model_h_tmp_stream << "#include <json/json.h>\n";
	model_h_tmp_stream << "#include <string>\n";
	model_h_tmp_stream << "#include <memory>\n";
	model_h_tmp_stream << "#include <vector>\n";
	model_h_tmp_stream << "#include <tuple>\n";
	model_h_tmp_stream << "#include <stdint.h>\n";
	model_h_tmp_stream << "#include <iostream>\n";
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "namespace drogon\n";
	model_h_tmp_stream << "{\n";
	model_h_tmp_stream << "namespace orm\n";
	model_h_tmp_stream << "{\n";
	model_h_tmp_stream << "class DbClient;\n";
	model_h_tmp_stream << "using DbClientPtr = std::shared_ptr<DbClient>;\n";
	model_h_tmp_stream << "}\n";
	model_h_tmp_stream << "}\n";
	model_h_tmp_stream << "namespace drogon_model\n";
	model_h_tmp_stream << "{\n";
	model_h_tmp_stream << "namespace ";
{
    auto & val=model_h_view_data["dbName"];
    if(val.type()==typeid(const char *)){
        model_h_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        model_h_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "{\n";
auto &schema=model_h_view_data.get<std::string>("schema");
    if(!schema.empty())
    {
        model_h_tmp_stream<<"namespace "<<schema<<"\n";
        model_h_tmp_stream<<"{\n";
    }
    std::vector<std::string> relationshipClassNames;
    auto &relationships=model_h_view_data.get<std::vector<Relationship>>("relationships");
    for(auto &relationship : relationships)
    {
        auto &name = relationship.targetTableName();
        auto relationshipClassName = nameTransform(name, true);
        relationshipClassNames.push_back(relationshipClassName);
        if(relationship.type() == Relationship::Type::ManyToMany)
        {
            auto &pivotTableName = relationship.pivotTable().tableName();
            auto pivotTableClassName = nameTransform(pivotTableName, true);
            relationshipClassNames.push_back(pivotTableClassName);
        }
    }
    std::sort(relationshipClassNames.begin(), relationshipClassNames.end());
    relationshipClassNames.erase(std::unique(relationshipClassNames.begin(), relationshipClassNames.end()), relationshipClassNames.end());
    for(std::string &relationshipClassName : relationshipClassNames)
    {
	model_h_tmp_stream << "class ";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << ";\n";
    }
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "class ";
{
    auto & val=model_h_view_data["className"];
    if(val.type()==typeid(const char *)){
        model_h_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        model_h_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "{\n";
	model_h_tmp_stream << "  public:\n";
	model_h_tmp_stream << "    struct Cols\n";
	model_h_tmp_stream << "    {\n";
auto cols=model_h_view_data.get<std::vector<ColumnInfo>>("columns");
    for(size_t i=0;i<cols.size();i++)
    {
        model_h_tmp_stream<<"        static const std::string _"<<cols[i].colName_<<";\n";
    }
	model_h_tmp_stream << "    };\n";
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "    const static int primaryKeyNumber;\n";
	model_h_tmp_stream << "    const static std::string tableName;\n";
	model_h_tmp_stream << "    const static bool hasPrimaryKey;\n";
if(model_h_view_data.get<int>("hasPrimaryKey")<=1){
	model_h_tmp_stream << "    const static std::string primaryKeyName;\n";
if(!model_h_view_data.get<std::string>("primaryKeyType").empty()){
	model_h_tmp_stream << "    using PrimaryKeyType = ";
{
    auto & val=model_h_view_data["primaryKeyType"];
    if(val.type()==typeid(const char *)){
        model_h_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        model_h_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
	model_h_tmp_stream << ";\n";
	model_h_tmp_stream << "    const PrimaryKeyType &getPrimaryKey() const;\n";
}else{
	model_h_tmp_stream << "    using PrimaryKeyType = void;\n";
	model_h_tmp_stream << "    int getPrimaryKey() const { assert(false); return 0; }\n";
}
}else{
    auto pkTypes=model_h_view_data.get<std::vector<std::string>>("primaryKeyType");
    std::string typelist;
    for(size_t i=0;i<pkTypes.size();i++)
    {
        typelist += pkTypes[i];
        if(i<(pkTypes.size()-1))
            typelist += ",";
    }
	model_h_tmp_stream << "    const static std::vector<std::string> primaryKeyName;\n";
	model_h_tmp_stream << "    using PrimaryKeyType = std::tuple<";
model_h_tmp_stream<<typelist;
	model_h_tmp_stream << ">;//";
    auto pkName=model_h_view_data.get<std::vector<std::string>>("primaryKeyName");
    for(size_t i=0;i<pkName.size();i++)
    {
        model_h_tmp_stream<<pkName[i];
        if(i<(pkName.size()-1))
            model_h_tmp_stream<<",";
    }
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "    PrimaryKeyType getPrimaryKey() const;\n";
}
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "    /**\n";
	model_h_tmp_stream << "     * @brief constructor\n";
	model_h_tmp_stream << "     * @param r One row of records in the SQL query result.\n";
	model_h_tmp_stream << "     * @param indexOffset Set the offset to -1 to access all columns by column names,\n";
	model_h_tmp_stream << "     * otherwise access all columns by offsets.\n";
	model_h_tmp_stream << "     * @note If the SQL is not a style of 'select * from table_name ...' (select all\n";
	model_h_tmp_stream << "     * columns by an asterisk), please set the offset to -1.\n";
	model_h_tmp_stream << "     */\n";
	model_h_tmp_stream << "    explicit ";
{
    auto & val=model_h_view_data["className"];
    if(val.type()==typeid(const char *)){
        model_h_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        model_h_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
	model_h_tmp_stream << "(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;\n";
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "    /**\n";
	model_h_tmp_stream << "     * @brief constructor\n";
	model_h_tmp_stream << "     * @param pJson The json object to construct a new instance.\n";
	model_h_tmp_stream << "     */\n";
	model_h_tmp_stream << "    explicit ";
{
    auto & val=model_h_view_data["className"];
    if(val.type()==typeid(const char *)){
        model_h_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        model_h_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
	model_h_tmp_stream << "(const Json::Value &pJson) noexcept(false);\n";
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "    /**\n";
	model_h_tmp_stream << "     * @brief constructor\n";
	model_h_tmp_stream << "     * @param pJson The json object to construct a new instance.\n";
	model_h_tmp_stream << "     * @param pMasqueradingVector The aliases of table columns.\n";
	model_h_tmp_stream << "     */\n";
	model_h_tmp_stream << "    ";
{
    auto & val=model_h_view_data["className"];
    if(val.type()==typeid(const char *)){
        model_h_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        model_h_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
	model_h_tmp_stream << "(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);\n";
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "    ";
{
    auto & val=model_h_view_data["className"];
    if(val.type()==typeid(const char *)){
        model_h_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        model_h_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
	model_h_tmp_stream << "() = default;\n";
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "    void updateByJson(const Json::Value &pJson) noexcept(false);\n";
	model_h_tmp_stream << "    void updateByMasqueradedJson(const Json::Value &pJson,\n";
	model_h_tmp_stream << "                                 const std::vector<std::string> &pMasqueradingVector) noexcept(false);\n";
	model_h_tmp_stream << "    static bool validateJsonForCreation(const Json::Value &pJson, std::string &err);\n";
	model_h_tmp_stream << "    static bool validateMasqueradedJsonForCreation(const Json::Value &,\n";
	model_h_tmp_stream << "                                                const std::vector<std::string> &pMasqueradingVector,\n";
	model_h_tmp_stream << "                                                    std::string &err);\n";
	model_h_tmp_stream << "    static bool validateJsonForUpdate(const Json::Value &pJson, std::string &err);\n";
	model_h_tmp_stream << "    static bool validateMasqueradedJsonForUpdate(const Json::Value &,\n";
	model_h_tmp_stream << "                                          const std::vector<std::string> &pMasqueradingVector,\n";
	model_h_tmp_stream << "                                          std::string &err);\n";
	model_h_tmp_stream << "    static bool validJsonOfField(size_t index,\n";
	model_h_tmp_stream << "                          const std::string &fieldName,\n";
	model_h_tmp_stream << "                          const Json::Value &pJson,\n";
	model_h_tmp_stream << "                          std::string &err,\n";
	model_h_tmp_stream << "                          bool isForCreation);\n";
model_h_tmp_stream<<"\n";
    for(const auto &col:cols)
    {
        model_h_tmp_stream<<"    /**  For column "<<col.colName_<<"  */\n";
        if(!col.colType_.empty())
        {
            model_h_tmp_stream<<"    ///Get the value of the column "<<col.colName_<<", returns the default value if the column is null\n";
            model_h_tmp_stream<<"    const "<<col.colType_<<" &getValueOf"<<col.colTypeName_<<"() const noexcept;\n";
            if(col.colType_=="std::vector<char>")
            {
                model_h_tmp_stream<<"    ///Return the column value by std::string with binary data\n";
                model_h_tmp_stream<<"    std::string getValueOf"<<col.colTypeName_<<"AsString() const noexcept;\n";
            }
            model_h_tmp_stream<<"    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null\n";
            model_h_tmp_stream<<"    const std::shared_ptr<"<<col.colType_<<"> &get"<<col.colTypeName_<<"() const noexcept;\n";
            model_h_tmp_stream<<"    ///Set the value of the column "<<col.colName_<<"\n";
            model_h_tmp_stream<<"    void set"<<col.colTypeName_<<"(const "<<col.colType_<<" &p"<<col.colTypeName_<<") noexcept;\n";
                if(col.colType_=="std::string")
                    model_h_tmp_stream<<"    void set"<<col.colTypeName_<<"("<<col.colType_<<" &&p"<<col.colTypeName_<<") noexcept;\n";
                if(col.colType_=="std::vector<char>")
                {
                    model_h_tmp_stream<<"    void set"<<col.colTypeName_<<"(const std::string &p"<<col.colTypeName_<<") noexcept;\n";
                }
                if(!col.notNull_)
                {
                    model_h_tmp_stream<<"    void set"<<col.colTypeName_<<"ToNull() noexcept;\n";
                }
        }
        else
            model_h_tmp_stream<<"    //FIXME!!"<<" getValueOf"<<col.colTypeName_<<"() const noexcept;\n";
        model_h_tmp_stream<<"\n";
    }
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "    static size_t getColumnNumber() noexcept {  return ";
model_h_tmp_stream<<cols.size();
	model_h_tmp_stream << ";  }\n";
	model_h_tmp_stream << "    static const std::string &getColumnName(size_t index) noexcept(false);\n";
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "    Json::Value toJson() const;\n";
	model_h_tmp_stream << "    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;\n";
	model_h_tmp_stream << "    /// Relationship interfaces\n";
    for(auto &relationship : relationships)
    {
        if(relationship.targetKey().empty() || relationship.originalKey().empty())
        {
            continue;
        }
        auto &name=relationship.targetTableName();
        auto relationshipClassName=nameTransform(name, true);
        auto relationshipValName=nameTransform(name, false);
        auto alias=relationship.targetTableAlias();
        auto aliasValName=nameTransform(alias, false);
        if(relationship.type() == Relationship::Type::HasOne)
        {
            if(!alias.empty())
            {
                if(alias[0] <= 'z' && alias[0] >= 'a')
                {
                    alias[0] += ('A' - 'a');
                }
                std::string alind(alias.length(), ' ');
	model_h_tmp_stream << "    ";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << " get";
model_h_tmp_stream<<alias;
	model_h_tmp_stream << "(const drogon::orm::DbClientPtr &clientPtr) const;\n";
	model_h_tmp_stream << "    void get";
model_h_tmp_stream<<alias;
	model_h_tmp_stream << "(const drogon::orm::DbClientPtr &clientPtr,\n";
	model_h_tmp_stream << "            ";
model_h_tmp_stream<<alind;
	model_h_tmp_stream << " const std::function<void(";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << ")> &rcb,\n";
	model_h_tmp_stream << "            ";
model_h_tmp_stream<<alind;
	model_h_tmp_stream << " const drogon::orm::ExceptionCallback &ecb) const;\n";
            }
            else
            {
                std::string relationshipClassInde(relationshipClassName.length(), ' ');
	model_h_tmp_stream << "    ";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << " get";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << "(const drogon::orm::DbClientPtr &clientPtr) const;\n";
	model_h_tmp_stream << "    void get";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << "(const drogon::orm::DbClientPtr &clientPtr,\n";
	model_h_tmp_stream << "            ";
model_h_tmp_stream<<relationshipClassInde;
	model_h_tmp_stream << " const std::function<void(";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << ")> &rcb,\n";
	model_h_tmp_stream << "            ";
model_h_tmp_stream<<relationshipClassInde;
	model_h_tmp_stream << " const drogon::orm::ExceptionCallback &ecb) const;\n";
            }
        }
        else if(relationship.type() == Relationship::Type::HasMany)
        {
            if(!alias.empty())
            {
                if(alias[0] <= 'z' && alias[0] >= 'a')
                {
                    alias[0] += ('A' - 'a');
                }
                std::string alind(alias.length(), ' ');
	model_h_tmp_stream << "    std::vector<";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << "> get";
model_h_tmp_stream<<alias;
	model_h_tmp_stream << "(const drogon::orm::DbClientPtr &clientPtr) const;\n";
	model_h_tmp_stream << "    void get";
model_h_tmp_stream<<alias;
	model_h_tmp_stream << "(const drogon::orm::DbClientPtr &clientPtr,\n";
	model_h_tmp_stream << "            ";
model_h_tmp_stream<<alind;
	model_h_tmp_stream << " const std::function<void(std::vector<";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << ">)> &rcb,\n";
	model_h_tmp_stream << "            ";
model_h_tmp_stream<<alind;
	model_h_tmp_stream << " const drogon::orm::ExceptionCallback &ecb) const;\n";
            }
            else
            {
                std::string relationshipClassInde(relationshipClassName.length(), ' ');
	model_h_tmp_stream << "    std::vector<";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << "> get";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << "(const drogon::orm::DbClientPtr &clientPtr) const;\n";
	model_h_tmp_stream << "    void get";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << "(const drogon::orm::DbClientPtr &clientPtr,\n";
	model_h_tmp_stream << "            ";
model_h_tmp_stream<<relationshipClassInde;
	model_h_tmp_stream << " const std::function<void(std::vector<";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << ">)> &rcb,\n";
	model_h_tmp_stream << "            ";
model_h_tmp_stream<<relationshipClassInde;
	model_h_tmp_stream << " const drogon::orm::ExceptionCallback &ecb) const;\n";
            }
        }
        else if(relationship.type() == Relationship::Type::ManyToMany)
        {
            auto &pivotTableName=relationship.pivotTable().tableName();
            auto pivotTableClassName=nameTransform(pivotTableName, true);
            if(!alias.empty())
            {
                if(alias[0] <= 'z' && alias[0] >= 'a')
                {
                    alias[0] += ('A' - 'a');
                }
                std::string alind(alias.length(), ' ');
	model_h_tmp_stream << "    std::vector<std::pair<";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << ",";
model_h_tmp_stream<<pivotTableClassName;
	model_h_tmp_stream << ">> get";
model_h_tmp_stream<<alias;
	model_h_tmp_stream << "(const drogon::orm::DbClientPtr &clientPtr) const;\n";
	model_h_tmp_stream << "    void get";
model_h_tmp_stream<<alias;
	model_h_tmp_stream << "(const drogon::orm::DbClientPtr &clientPtr,\n";
	model_h_tmp_stream << "            ";
model_h_tmp_stream<<alind;
	model_h_tmp_stream << " const std::function<void(std::vector<std::pair<";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << ",";
model_h_tmp_stream<<pivotTableClassName;
	model_h_tmp_stream << ">>)> &rcb,\n";
	model_h_tmp_stream << "            ";
model_h_tmp_stream<<alind;
	model_h_tmp_stream << " const drogon::orm::ExceptionCallback &ecb) const;\n";
            }
            else
            {
                std::string relationshipClassInde(relationshipClassName.length(), ' ');
	model_h_tmp_stream << "    std::vector<std::pair<";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << ",";
model_h_tmp_stream<<pivotTableClassName;
	model_h_tmp_stream << ">> get";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << "(const drogon::orm::DbClientPtr &clientPtr) const;\n";
	model_h_tmp_stream << "    void get";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << "(const drogon::orm::DbClientPtr &clientPtr,\n";
	model_h_tmp_stream << "            ";
model_h_tmp_stream<<relationshipClassInde;
	model_h_tmp_stream << " const std::function<void(std::vector<std::pair<";
model_h_tmp_stream<<relationshipClassName;
	model_h_tmp_stream << ",";
model_h_tmp_stream<<pivotTableClassName;
	model_h_tmp_stream << ">>)> &rcb,\n";
	model_h_tmp_stream << "            ";
model_h_tmp_stream<<relationshipClassInde;
	model_h_tmp_stream << " const drogon::orm::ExceptionCallback &ecb) const;\n";
            }
        }
    }
	model_h_tmp_stream << "  private:\n";
	model_h_tmp_stream << "    friend drogon::orm::Mapper<";
{
    auto & val=model_h_view_data["className"];
    if(val.type()==typeid(const char *)){
        model_h_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        model_h_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
	model_h_tmp_stream << ">;\n";
	model_h_tmp_stream << "#ifdef __cpp_impl_coroutine\n";
	model_h_tmp_stream << "    friend drogon::orm::CoroMapper<";
{
    auto & val=model_h_view_data["className"];
    if(val.type()==typeid(const char *)){
        model_h_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        model_h_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
	model_h_tmp_stream << ">;\n";
	model_h_tmp_stream << "#endif\n";
	model_h_tmp_stream << "    static const std::vector<std::string> &insertColumns() noexcept;\n";
	model_h_tmp_stream << "    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;\n";
	model_h_tmp_stream << "    const std::vector<std::string> updateColumns() const;\n";
	model_h_tmp_stream << "    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;\n";
	model_h_tmp_stream << "    ///For mysql or sqlite3\n";
	model_h_tmp_stream << "    void updateId(const uint64_t id);\n";
    for(auto col:cols)
    {
        if(!col.colType_.empty())
            model_h_tmp_stream<<"    std::shared_ptr<"<<col.colType_<<"> "<<col.colValName_<<"_;\n";
    }
    
	model_h_tmp_stream << "    struct MetaData\n";
	model_h_tmp_stream << "    {\n";
	model_h_tmp_stream << "        const std::string colName_;\n";
	model_h_tmp_stream << "        const std::string colType_;\n";
	model_h_tmp_stream << "        const std::string colDatabaseType_;\n";
	model_h_tmp_stream << "        const ssize_t colLength_;\n";
	model_h_tmp_stream << "        const bool isAutoVal_;\n";
	model_h_tmp_stream << "        const bool isPrimaryKey_;\n";
	model_h_tmp_stream << "        const bool notNull_;\n";
	model_h_tmp_stream << "    };\n";
	model_h_tmp_stream << "    static const std::vector<MetaData> metaData_;\n";
	model_h_tmp_stream << "    bool dirtyFlag_[";
model_h_tmp_stream<<cols.size();
	model_h_tmp_stream << "]={ false };\n";
	model_h_tmp_stream << "  public:\n";
	model_h_tmp_stream << "    static const std::string &sqlForFindingByPrimaryKey()\n";
	model_h_tmp_stream << "    {\n";
auto rdbms=model_h_view_data.get<std::string>("rdbms");
if(model_h_view_data.get<int>("hasPrimaryKey")<=1){
        if(!model_h_view_data.get<std::string>("primaryKeyType").empty()){
	model_h_tmp_stream << "        static const std::string sql=\"select * from \" + tableName + \" where ";
{
    auto & val=model_h_view_data["primaryKeyName"];
    if(val.type()==typeid(const char *)){
        model_h_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        model_h_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
	model_h_tmp_stream << " = ";
model_h_tmp_stream<<(rdbms=="postgresql"?"$1":"?");
	model_h_tmp_stream << "\";\n";
}else{
	model_h_tmp_stream << "        static const std::string sql=\"\";\n";
}
}else{
        auto pkName=model_h_view_data.get<std::vector<std::string>>("primaryKeyName");
	model_h_tmp_stream << "        static const std::string sql=\"select * from \" + tableName + \" where ";
        for(size_t i=0;i<pkName.size();i++)
        {
            if(rdbms=="postgresql")
            {
                model_h_tmp_stream<<pkName[i]<<" = $"<<i+1;
            }
            else
            {
                model_h_tmp_stream<<pkName[i]<<" = ?";
            }
            if(i<(pkName.size()-1))
                model_h_tmp_stream<<" and ";
        }
        model_h_tmp_stream<<"\";\n";
    }
	model_h_tmp_stream << "        return sql;\n";
	model_h_tmp_stream << "    }\n";
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "    static const std::string &sqlForDeletingByPrimaryKey()\n";
	model_h_tmp_stream << "    {\n";
if(model_h_view_data.get<int>("hasPrimaryKey")<=1){
        if(!model_h_view_data.get<std::string>("primaryKeyType").empty()){
	model_h_tmp_stream << "        static const std::string sql=\"delete from \" + tableName + \" where ";
{
    auto & val=model_h_view_data["primaryKeyName"];
    if(val.type()==typeid(const char *)){
        model_h_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        model_h_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
	model_h_tmp_stream << " = ";
model_h_tmp_stream<<(rdbms=="postgresql"?"$1":"?");
	model_h_tmp_stream << "\";\n";
}else{
	model_h_tmp_stream << "        static const std::string sql=\"\";\n";
}
}else{
        auto pkName=model_h_view_data.get<std::vector<std::string>>("primaryKeyName");
	model_h_tmp_stream << "        static const std::string sql=\"delete from \" + tableName + \" where ";
        for(size_t i=0;i<pkName.size();i++)
        {
            if(rdbms=="postgresql")
            {
                model_h_tmp_stream<<pkName[i]<<" = $"<<i+1;
            }
            else
            {
                model_h_tmp_stream<<pkName[i]<<" = ?";
            }
            if(i<(pkName.size()-1))
                model_h_tmp_stream<<" and ";
        }
        model_h_tmp_stream<<"\";\n";
    }
	model_h_tmp_stream << "        return sql;\n";
	model_h_tmp_stream << "    }\n";
	model_h_tmp_stream << "    std::string sqlForInserting(bool &needSelection) const\n";
	model_h_tmp_stream << "    {\n";
	model_h_tmp_stream << "        std::string sql=\"insert into \" + tableName + \" (\";\n";
	model_h_tmp_stream << "        size_t parametersCount = 0;\n";
	model_h_tmp_stream << "        needSelection = false;\n";
        bool selFlag=false;
        for(size_t i=0;i<cols.size();i++)
        {
            if(cols[i].isAutoVal_)
            {
                if(model_h_view_data.get<std::string>("rdbms")=="sqlite3")
                {
                    continue;
                }
                if(model_h_view_data.get<int>("hasPrimaryKey")>0)
                {
                    selFlag = true;
                }
                model_h_tmp_stream<<"            sql += \""<<cols[i].colName_<<",\";\n";
                model_h_tmp_stream<<"            ++parametersCount;\n";
                continue;
            }
            if(cols[i].colType_.empty())
                continue;
            if(cols[i].hasDefaultVal_)
            {
                if(model_h_view_data.get<std::string>("rdbms")!="sqlite3")
                {
                    model_h_tmp_stream<<"        sql += \""<<cols[i].colName_<<",\";\n";
                    model_h_tmp_stream<<"        ++parametersCount;\n";
                }
                else
                {
	model_h_tmp_stream << "        if(dirtyFlag_[";
model_h_tmp_stream<<i;
	model_h_tmp_stream << "])\n";
	model_h_tmp_stream << "        {\n";
	model_h_tmp_stream << "            sql += \"";
model_h_tmp_stream<<cols[i].colName_;
	model_h_tmp_stream << ",\";\n";
	model_h_tmp_stream << "            ++parametersCount;\n";
	model_h_tmp_stream << "        }\n";
                }
                if(model_h_view_data.get<int>("hasPrimaryKey")>0||model_h_view_data.get<std::string>("rdbms")=="postgresql")
                {
	model_h_tmp_stream << "        if(!dirtyFlag_[";
model_h_tmp_stream<<i;
	model_h_tmp_stream << "])\n";
	model_h_tmp_stream << "        {\n";
	model_h_tmp_stream << "            needSelection=true;\n";
	model_h_tmp_stream << "        }\n";
                }
            }
            else
            {
	model_h_tmp_stream << "        if(dirtyFlag_[";
model_h_tmp_stream<<i;
	model_h_tmp_stream << "])\n";
	model_h_tmp_stream << "        {\n";
	model_h_tmp_stream << "            sql += \"";
model_h_tmp_stream<<cols[i].colName_;
	model_h_tmp_stream << ",\";\n";
	model_h_tmp_stream << "            ++parametersCount;\n";
	model_h_tmp_stream << "        }\n";
            }
        }
        if(selFlag)
        {
            model_h_tmp_stream<<"        needSelection=true;\n";
        }
	model_h_tmp_stream << "        if(parametersCount > 0)\n";
	model_h_tmp_stream << "        {\n";
	model_h_tmp_stream << "            sql[sql.length()-1]=')';\n";
	model_h_tmp_stream << "            sql += \" values (\";\n";
	model_h_tmp_stream << "        }\n";
	model_h_tmp_stream << "        else\n";
	model_h_tmp_stream << "            sql += \") values (\";\n";
model_h_tmp_stream<<"\n";
if(model_h_view_data.get<std::string>("rdbms")=="postgresql")
{
	model_h_tmp_stream << "        int placeholder=1;\n";
	model_h_tmp_stream << "        char placeholderStr[64];\n";
	model_h_tmp_stream << "        size_t n=0;\n";
}
        for(size_t i=0;i<cols.size();i++)
        {
        if(cols[i].isAutoVal_)
        {
            if(model_h_view_data.get<std::string>("rdbms")!="sqlite3")
            {
	model_h_tmp_stream << "        sql +=\"default,\";\n";
            }
            continue;
        }
        if(cols[i].colType_.empty())
        continue;
	model_h_tmp_stream << "        if(dirtyFlag_[";
model_h_tmp_stream<<i;
	model_h_tmp_stream << "])\n";
	model_h_tmp_stream << "        {\n";
                if(model_h_view_data.get<std::string>("rdbms")=="postgresql")
                {
	model_h_tmp_stream << "            n = sprintf(placeholderStr,\"$%d,\",placeholder++);\n";
	model_h_tmp_stream << "            sql.append(placeholderStr, n);\n";
                }else
                {
	model_h_tmp_stream << "            sql.append(\"?,\");\n";
model_h_tmp_stream<<"\n";
                }
	model_h_tmp_stream << "        }\n";
if(cols[i].hasDefaultVal_&&model_h_view_data.get<std::string>("rdbms")!="sqlite3")
{
	model_h_tmp_stream << "        else\n";
	model_h_tmp_stream << "        {\n";
	model_h_tmp_stream << "            sql +=\"default,\";\n";
	model_h_tmp_stream << "        }\n";
}
        }
	model_h_tmp_stream << "        if(parametersCount > 0)\n";
	model_h_tmp_stream << "        {\n";
	model_h_tmp_stream << "            sql.resize(sql.length() - 1);\n";
	model_h_tmp_stream << "        }\n";
        if(rdbms=="postgresql")
        {
	model_h_tmp_stream << "        if(needSelection)\n";
	model_h_tmp_stream << "        {\n";
	model_h_tmp_stream << "            sql.append(\") returning *\");\n";
	model_h_tmp_stream << "        }\n";
	model_h_tmp_stream << "        else\n";
	model_h_tmp_stream << "        {\n";
	model_h_tmp_stream << "            sql.append(1, ')');\n";
	model_h_tmp_stream << "        }\n";
        }
        else
        {
            model_h_tmp_stream<<"        sql.append(1, ')');\n";
        }
	model_h_tmp_stream << "        LOG_TRACE << sql;\n";
	model_h_tmp_stream << "        return sql;\n";
	model_h_tmp_stream << "    }\n";
	model_h_tmp_stream << "};\n";
if(!schema.empty())
{
    model_h_tmp_stream<<"} // namespace "<<schema<<"\n";
}
	model_h_tmp_stream << "} // namespace ";
{
    auto & val=model_h_view_data["dbName"];
    if(val.type()==typeid(const char *)){
        model_h_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        model_h_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
model_h_tmp_stream<<"\n";
	model_h_tmp_stream << "} // namespace drogon_model\n";
if(layoutName.empty())
{
std::string ret{std::move(model_h_tmp_stream.str())};
return ret;
}else
{
auto templ = DrTemplateBase::newTemplate(layoutName);
if(!templ) return "";
HttpViewData data = model_h_view_data;
auto str = std::move(model_h_tmp_stream.str());
if(!str.empty() && str[str.length()-1] == '\n') str.resize(str.length()-1);
data[""] = std::move(str);
return templ->genText(data);
}
}
