#include "storage.h"

StorageController Storage = { lines, createFile, isEmptyFile, appendFile, writeFile, removeFile, clearFile, renameFile, copyFile };