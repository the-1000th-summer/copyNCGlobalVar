#include <cstring>
#include <iostream>
#include <netcdf>
#include <string>
#include <vector>

using namespace std;



void printErrMsg() {
    cout << "Invalid argument:"
         << "You should provide input and output file path!" << endl;
}
void printUsage() {
    cout << "Usage:\n"
         << "copyNCGlobalVar <input file path> <output file path>" << endl;
}

void checkArgument(int argc) {
    if (argc == 3) {
        return;
    }
    if (argc != 1) {
        printErrMsg();
    }
    printUsage();
}


void getValue(netCDF::NcGroupAtt ncAtt) {
    vector<string> typeNames = {"user_type", "byte", "char", "short", "int", "float", "double", "ubyte", "ushort", "uint", "int64", "uint64", "string"};
    
}

void doTheRealThing() {
    string ncFileDir = "/mnt/e/p_learn/cpp_learn/copyNCGlobalVar/testData/";
    string ncFilePath = ncFileDir + "so2_0.16_101902.nc";
    string outputFilePath = ncFileDir + "so2_0.16_101902_noZ.nc";
    netCDF::NcFile fileWithGlobalVar(ncFilePath, netCDF::NcFile::read);
    netCDF::NcFile outputFile(outputFilePath, netCDF::NcFile::write);

    // auto aa = fileWithGlobalVar.getAtt("TITLE");


    auto a = fileWithGlobalVar.getAtts();

    auto map_it = a.cbegin();
    while (map_it != a.cend()) {
        string ncAttName = map_it->first;
        cout << ncAttName << ": ";
        auto ncAtt = map_it->second;
        auto ncAttType = ncAtt.getType();
        cout << ncAttType.getName() << endl;
        
        if (ncAttType.getName() == "byte") {  // byte占用1字节空间
            char val;
            ncAtt.getValues(&val);
            outputFile.putAtt(ncAttName, ncAttType, val);
        }
        else if (ncAttType == netCDF::NcType::nc_CHAR) {   // 所有字符串类型都为char，即使用string写入文件，读出来的仍旧为char
            string val;
            ncAtt.getValues(val);
            outputFile.putAtt(ncAttName, val);
        }
        else if (ncAttType.getName() == "short") {
            short val;
            ncAtt.getValues(&val);
            outputFile.putAtt(ncAttName, ncAttType, val);
        }
        else if (ncAttType.getName() == "int") {
            int val;
            ncAtt.getValues(&val);
            outputFile.putAtt(ncAttName, ncAttType, val);
        }
        else if (ncAttType.getName() == "float") {
            float val;
            ncAtt.getValues(&val);
            outputFile.putAtt(ncAttName, ncAttType, val);
        }
        else if (ncAttType.getName() == "double") {
            double val;
            ncAtt.getValues(&val);
            outputFile.putAtt(ncAttName, ncAttType, val);
        }
        else if (ncAttType.getName() == "ubyte") {
            unsigned char val;
            ncAtt.getValues(&val);
            outputFile.putAtt(ncAttName, ncAttType, val);
        }
        else if (ncAttType.getName() == "ushort") {
            ushort val;
            ncAtt.getValues(&val);
            outputFile.putAtt(ncAttName, ncAttType, val);
        }
        else if (ncAttType.getName() == "uint") {
            uint val;
            ncAtt.getValues(&val);
            outputFile.putAtt(ncAttName, ncAttType, val);
        }
        else if (ncAttType.getName() == "int64") {
            long long val;
            ncAtt.getValues(&val);
            outputFile.putAtt(ncAttName, ncAttType, val);
        }
        else if (ncAttType.getName() == "uint64") {
            unsigned long long val;
            ncAtt.getValues(&val);
            outputFile.putAtt(ncAttName, ncAttType, val);
        }
        else if (ncAttType.getName() == "string") {
            string val;
            ncAtt.getValues(&val);
            outputFile.putAtt(ncAttName, val);
        }
        else {
            throw "unknown type!";
        }

        
        
        // cout << map_it->second.getType().getId() << endl;
        // cout << map_it->second.getType().getSize() << endl;

        
        // printValue(map_it->second);
        // string aa;
        // (map_it->second).getValues(&aa);
        // cout << aa << endl;
        // printValue<typename T>(netCDF::NcGroupAtt t)
        
        ++map_it;
    }

    fileWithGlobalVar.close();
    outputFile.close();
}

void checkType() {
    cout << netCDF::NcByte().getSize() << endl;
    cout << netCDF::NcChar().getSize() << endl;
    cout << netCDF::NcShort().getId() << endl;
    cout << netCDF::NcInt().getId() << endl;
    cout << netCDF::NcFloat().getId() << endl;
    cout << netCDF::NcDouble().getId() << endl;
    cout << netCDF::NcUbyte().getSize() << endl;
    cout << netCDF::NcUshort().getId() << endl;
    cout << netCDF::NcUint().getId() << endl;
    cout << netCDF::NcInt64().getId() << endl;
    cout << netCDF::NcUint64().getId() << endl;
    cout << netCDF::NcString().getName() << endl;
    cout << netCDF::NcVlenType().getName() << endl;
    cout << netCDF::NcOpaqueType().getId() << endl;
    cout << netCDF::NcEnumType().getId() << endl;
    cout << netCDF::NcCompoundType().getId() << endl;
}

void compareCharAndString() {

    string ncFileDir = "/mnt/e/p_learn/cpp_learn/copyNCGlobalVar/testData/";
    // string ncFilePath = ncFileDir + "so2_0.16_101902.nc";
    string outputFilePath = ncFileDir + "so2_0.16_101902_noZ.nc";
    // netCDF::NcFile fileWithGlobalVar(ncFilePath, netCDF::NcFile::read);
    // netCDF::NcFile outputFile(outputFilePath, netCDF::NcFile::write);
    netCDF::NcFile outputFile(outputFilePath, netCDF::NcFile::read);

    // auto aa = outputFile.getAtt("tryString");
    auto aa = outputFile.getAtt("tryChar");
    cout << aa.getType().getName() << endl;
    string bb;
    aa.getValues(bb);
    cout << bb << endl;
    // char a;
    // aa.getValues(&a);
    // cout << a << endl;

    // char c[100];
    // aa.getValues(c);
    // cout << c << "!" << endl;
    char a = 's';
    char *pa = &a;
    cout <<  strlen(pa) << endl;
    // auto b = &a;
    // cout << strlen(a) << endl;
    // outputFile.putAtt("tryChar", netCDF::NcType::nc_CHAR , 1, pa);
    // char a = 45;
    // cout << a << endl;
    // outputFile.putAtt("tryfloatInt", netCDF::NcType::nc_BYTE, a);
    // outputFile.putAtt("tryString", "sdfghjfg");

    // fileWithGlobalVar.close();
    outputFile.close();
}

int main(int argc, char *argv[]) {

    // checkArgument(argc);
    // checkType();
    compareCharAndString();
    
    // doTheRealThing();
    // cout << sizeof(char) << endl;
    // cout << sizeof(short) << endl;
    // cout << sizeof(int) << endl;
    // cout << sizeof(long) << endl;
    // cout << sizeof(long long) << endl;
    // cout << sizeof(unsigned long long) << endl;
    // cout << netCDF::NcByte().get() << endl;
}