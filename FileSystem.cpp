/*

---------------------------- In-memory File Structure------------------------------------ 

-> whole code is written in c++ 
-> file structure is used like windows format (/shantanu/videos/songs/Farewell.mkv)
-> Functionalities that can be done in whole project are - 
1) show all files in a given path
2) add file in a given path
3) write content in a file of given path
4) read content in a file of given path


Used concept:- 
                                                                     
                                            ------------------------------------------------------------------------------------------------------------------
                                            |                    |                            |                     |                      |                 |   
                                            |KEY-DIRECTORY MAP   |   Current Directory        |Directory MAP->VALUE | KEY->FILEMAP         | VALUE->FILEMAP  |   
                                            |                    |                            |    (SUbDirectory)   |                      |                 |
                                            -----------------------------------------------------------------------------------------------------------------|
                                            |                    |                            |                     |                      |                 |   
                                            |  /                 |            /               |  videos, documents  | /shantanu.cpp        |  shantanu.cpp   |    
                                            -----------------------------------------------------------------------------------------------------------------|
                                            |                    |                            |                     |                      |                 |
                                            |  /videos/          |         videos             |  songs              |/videos/Farewell.mkv  |  Farewell.mkv   |   
                                            -----------------------------------------------------------------------------------------------------------------|  
                                            |                    |                            |                     |                      |                 |
                                            | /Documents/        |         Documents          |  ShanDocs           |/Documents/Aadhar.docx|  Aadahar.docx   |
                                            -----------------------------------------------------------------------------------------------------------------|
                                            |                    |                            |                     |                      |                 |
                                            |/videos/Songs/      |         songs              |  EMPTY              |   EMPTY              |  EMPTY          |
                                            -----------------------------------------------------------------------------------------------------------------|
                                            |                    |                            |                     |                      |                 |
                                            |/Documents/ShanDocs/|         ShanDocs           |  EMPTY              |   EMPTY              |  EMPTY          |
                                            ------------------------------------------------------------------------------------------------------------------
                                      
*/


/* FileSystem will contain following declaration and functions-

* An unordered map(dirs) to map between current directory path and subdirectories.

* An unordered map(files) to map between FilePath and files.

* Unordered map is used as it is designed by hashing so it will be good for large memrory. Best case to read and write will be O(1).  

Functions -> 

1) ls -> This function will return all the files in a given path if existed and subdirectories. 

2) MakeDirectory -> This function will create a directory and subdirectory of the given path.

3) AddSomethingToFile -> This function will first check if a given path existed or not, then in case if it is not, it will first create one then write or else it will write.

4) ReadFile -> If a given FilePath is existed, it return content of it. 

*/

#include<bits/stdc++.h>
using namespace std;


class FileSystem
{
    private:
        
        unordered_map<string, set<string>> directories;
        unordered_map<string, string> files;

    public:
        

/* constructor will create root directory as / */
        FileSystem()
        {
            directories["/"];
        }


/*  ls function will first check the last string of path which can be a file(if existed), it will return it

    in case if there is no file, it will return the subdirectories from directory map. 

*/
        vector<string> ls(string path)
        {
            if(files.count(path))
            {
                int idx = path.find_last_of('/');
                return {path.substr(idx + 1)};
            }

            auto t = directories[path];
            return vector<string>(t.begin(), t.end());
        }

/* string of path will be passed to istringsream object
  string CurrentDirectory will consist current directory
  string dir will consist whole path that has been visited till
  getline()function will split the string from the character '/' each time and save it into string CurrentDirectory.
  everytime CurrentDirectory will consist a subdirectory that will be saved to directory map by using key dir which will consist the path of directory   
*/

        void MakeDirectory(string path)
        {
            istringstream is(path);
            string CurrentDirectory = "";
            string DirectoryPathNow = "";            

            while(getline(is, CurrentDirectory, '/'))
            {
                if(CurrentDirectory.empty())
                    continue;

                if(DirectoryPathNow.empty())
                    DirectoryPathNow += "/";

                directories[DirectoryPathNow].insert(CurrentDirectory);

                if(DirectoryPathNow.size() > 1)
                    DirectoryPathNow += "/";
                
                DirectoryPathNow += CurrentDirectory;
            }
        }

/*
 find_last_of() will eturn the last of index of path which will be an index of file address and stored into IndexOfLast.
 So now from start to till IndexOfLast will contain the path of file and stored into DirectoryPath.
 Name of file is stored in file string.
 In case if given path of file is not existed, create one and then save the content of file.  

*/

        void AddSomethingToFile(string FilePath, string content)
        {
            int IndexOfLast = FilePath.find_last_of('/');
            string DirectoryPath = FilePath.substr(0, IndexOfLast);
            string file = FilePath.substr(IndexOfLast + 1);

            if(DirectoryPath.empty())
                DirectoryPath = "/";

            if(!directories.count(DirectoryPath))
                MakeDirectory(DirectoryPath);

            directories[DirectoryPath].insert(file);
            files[FilePath].append(content);
            
        }

/*
 If a FilePath is existed return its content from filemap. 
*/
        string ReadFile(string FilePath)
        {
            return files[FilePath];
        }

};

int main()
{
    FileSystem obj;

    obj.MakeDirectory("/shan/videos");
    obj.MakeDirectory("/shan/Documents"); 

    vector<string>:: iterator i;
    vector<string>l = obj.ls("/shan");

     for (i = l.begin(); i != l.end(); ++i)
        cout << *i << '\t';

    AddSomethingToFile("/shan/Documents/exm.txt", "I love code");

    string f = ReadFile("/shan/Documents/exm.txt");
    cout<<endl<<f<<endl;


    return 0;
    

}



