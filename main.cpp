#include <cstring>
#include <iostream>
#include <netcdf>
#include <string>
#include <sys/types.h>
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

template <typename T>
inline void getValAndWriteToFile(netCDF::NcFile &oFile, const netCDF::NcGroupAtt &ncAtt) {
    T val;
    ncAtt.getValues(&val);
    oFile.putAtt(ncAtt.getName(), ncAtt.getType(), val);
}

void doTheRealThing() {
    string ncFileDir = "/mnt/e/p_learn/cpp_learn/copyNCGlobalVar/testData/";
    string ncFilePath = ncFileDir + "so2_0.16_101902.nc";
    string outputFilePath = ncFileDir + "so2_0.16_101902_noZ.nc";
    netCDF::NcFile fileWithGlobalVar(ncFilePath, netCDF::NcFile::read);
    netCDF::NcFile outputFile(outputFilePath, netCDF::NcFile::write);

    auto ncAtts = fileWithGlobalVar.getAtts();

    auto map_it = ncAtts.cbegin();
    while (map_it != ncAtts.cend()) {
        auto ncAtt = map_it->second;
        auto ncAttTypeClass = ncAtt.getType().getTypeClass();
        
        switch (ncAttTypeClass) {
        case netCDF::NcType::nc_INT:
            getValAndWriteToFile<int>(outputFile, ncAtt);
            break;
        case netCDF::NcType::nc_FLOAT:
            getValAndWriteToFile<float>(outputFile, ncAtt);
            break;
        case netCDF::NcType::nc_CHAR: case netCDF::NcType::nc_STRING: {
            string val;
            ncAtt.getValues(val);
            outputFile.putAtt(ncAtt.getName(), val);
            break;
        }
        case netCDF::NcType::nc_DOUBLE:
            getValAndWriteToFile<double>(outputFile, ncAtt);
            break;
        case netCDF::NcType::nc_SHORT:
            getValAndWriteToFile<short>(outputFile, ncAtt);
            break;
        case netCDF::NcType::nc_BYTE:
            getValAndWriteToFile<char>(outputFile, ncAtt);
            break;
        case netCDF::NcType::nc_UBYTE:
            getValAndWriteToFile<unsigned char>(outputFile, ncAtt);
            break;
        case netCDF::NcType::nc_USHORT:
            getValAndWriteToFile<ushort>(outputFile, ncAtt);
            break;
        case netCDF::NcType::nc_UINT:
            getValAndWriteToFile<uint>(outputFile, ncAtt);
            break;
        case netCDF::NcType::nc_INT64:
            getValAndWriteToFile<long long>(outputFile, ncAtt);
            break;
        case netCDF::NcType::nc_UINT64:
            getValAndWriteToFile<unsigned long long>(outputFile, ncAtt);
            break;
        default:
            throw "unknown type!";
        }
        
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
    // compareCharAndString();
    
    doTheRealThing();
    // cout << sizeof(char) << endl;
    // cout << sizeof(short) << endl;
    // cout << sizeof(int) << endl;
    // cout << sizeof(long) << endl;
    // cout << sizeof(long long) << endl;
    // cout << sizeof(unsigned long long) << endl;
    // cout << netCDF::NcByte().get() << endl;
}