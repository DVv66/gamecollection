#include <stdio.h>
#include <windows.h>
#include <string.h>

const int MAX_FILENAME_LEN = 256;

const char* original_folder = "D:\\desktop\\test";//这个是原来的
const char* target_folder = "D:\\desktop\\test1";//这个改成目标文件夹

int endsWith(const char* str, const char* suffix) {
    if (!str || !suffix) {
        return 0;
    }
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix > lenstr) {
        return 0;
    }
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0 ? 1 : 0;
}

int main() {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    int file_count = 0;

    char original_search_path[MAX_FILENAME_LEN];
    sprintf_s(original_search_path, "%s\\*.*", original_folder);

    hFind = FindFirstFile(original_search_path, &findFileData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (endsWith(findFileData.cFileName, ".jpg") || endsWith(findFileData.cFileName, ".jpeg") || endsWith(findFileData.cFileName, ".png")) {
                char old_filepath[MAX_FILENAME_LEN];
                char new_filename[MAX_FILENAME_LEN];

                sprintf_s(old_filepath, "%s\\%s", original_folder, findFileData.cFileName);

                file_count++;
                sprintf_s(new_filename, "ZZZ%d.jpg", file_count);
                char new_filepath[MAX_FILENAME_LEN];
                sprintf_s(new_filepath, "%s\\%s", target_folder, new_filename);

                if (!CopyFile(old_filepath, new_filepath, FALSE)) {
                    printf("复制文件失败\n");
                    continue;
                }
            }
        } while (FindNextFile(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
    else {
        perror("");
        return 1;
    }

    return 0;
}
