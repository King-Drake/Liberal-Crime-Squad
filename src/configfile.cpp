


#include "includes52.h"
#include "constStringconfigfile.h"
#include <algorithm>
#include <fstream>

std::ifstream* openFile(const std::string& filename, std::ios_base::openmode format)
{
   std::ifstream* file = new std::ifstream();
   addstrAlt(ATTEMPTING_TO_OPEN);
   addstrAlt(filename);
   addstrAlt(singleSpace);
   file->open((artdir+filename).c_str(), format);
   return file;
}
// Reads in an entire configuration file
// Returns true for read successful, returns false if failed read
int readConfigFile(const std::string& filename)
{
   std::string command, value;
   configurable* object=0;
   std::ifstream* file = openFile(filename, std::ios::in);
   if(!file->is_open())
   {
      delete file;
      return false; // Unable to open; failed read
   }
   // loop through lines
   while(readLine(*file, command, value))
      // if COMMAND is OBJECT,
      // call a object creator factory, passing VALUE
      // (record pointer to that object)
      if(command==CONST_X_OBJECT) object=createObject(value);
      // if I have an object,
      // pass COMMAND and VALUE to the object
      else if(object) object->configure(command, value);
      else
      {
         file->close();
         delete file;
         return false; // Unknown command and no object to give it to; failed read
      }
   file->close();
   delete file;
   return true;
}
// readLine reads a line from the file, parses it
int readLine(std::ifstream& file, std::string& command, std::string& value)
{
   std::string line;
   int source=0;
   // Search for a non-comment, non-empty line
   do
   {
      if(file.eof()) return false;
      getline(file,line);
      line.erase(std::remove(line.begin(),line.end(),'\r'),line.end());
      line.erase(std::remove(line.begin(),line.end(),'\n'),line.end());
   } while(!len(line)||line[0]=='#');
   // Parse the line
   command.clear();
   value.clear();
   // Leading whitespace
   for(;source<len(line)&&(line[source]==' '||line[source]=='\t');source++);
   // Command
   for(;source<len(line)&&(line[source]!=' '&&line[source]!='\t');command.push_back(line[source++]));
   // Delimiting whitespace
   for(;source<len(line)&&(line[source]==' '||line[source]=='\t');source++);
   // Value
   for(;source<len(line)&&(line[source]!=' '&&line[source]!='\t');value.push_back(line[source++]));
   return true;
}
void readMapCBSpecials(int x, int y, int z, int i)
{
	if (mapCBSpecial.count(i) > 0) {
		levelmap[x][y][z].special = mapCBSpecial[i];
	}
	else {
		levelmap[x][y][z].special = mapCBSpecial[0];
	}
}
void makeDoor(int x,int y,int z,int flags=0)
{
   levelmap[x][y][z].flag=SITEBLOCK_DOOR|flags;
   if((x>0&&(levelmap[x-1][y][z].flag&SITEBLOCK_RESTRICTED))||
      (y>0&&(levelmap[x][y-1][z].flag&SITEBLOCK_RESTRICTED)))
      levelmap[x][y][z].flag|=SITEBLOCK_RESTRICTED;
}
void readMapCBTiles(int x, int y, int z, int i)
{
   switch(i)
   {
   default:
   case 0: levelmap[x][y][z].flag=0; break;
   case 2: levelmap[x][y][z].flag=SITEBLOCK_BLOCK; break;
   case 3: levelmap[x][y][z].flag=SITEBLOCK_EXIT; break;
   case 4: levelmap[x][y][z].flag=SITEBLOCK_GRASSY; break;
   case 5: makeDoor(x,y,z); break;
   case 6: makeDoor(x,y,z,SITEBLOCK_LOCKED); break;
   case 7:
      levelmap[x][y][z].flag=SITEBLOCK_RESTRICTED;
      if(x>0&&(levelmap[x-1][y][z].flag&SITEBLOCK_DOOR))
         levelmap[x-1][y][z].flag|=SITEBLOCK_RESTRICTED;
      if(y>0&&(levelmap[x][y-1][z].flag&SITEBLOCK_DOOR))
         levelmap[x][y-1][z].flag|=SITEBLOCK_RESTRICTED;
      break;
   case 8: levelmap[x][y][z].flag=SITEBLOCK_CHAINLINK; break;
   case 9: makeDoor(x,y,z,SITEBLOCK_LOCKED|SITEBLOCK_ALARMED); break;
   case 10: levelmap[x][y][z].flag=SITEBLOCK_BLOCK|SITEBLOCK_METAL; break;
   case 11: makeDoor(x,y,z,SITEBLOCK_LOCKED|SITEBLOCK_METAL); break;
   }
}
bool readMapFile(const string &filename, const int zLevel, void (*callback)(int,int,int,int))
{
   // open the file in question
   std::ifstream* file = openFile(filename, std::ios::in);
   // abort if the file couldn't be opened
   if(!file->is_open())
   {
      delete file;
      return false;
   }
   for(int y=0,z=zLevel;!file->eof();y++)
   {
      std::string line;
      getline(*file,line);
      line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
      line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
      for(int x=0,i=0,j=0;j<len(line);x++,i=++j)
      {
         for(;j<len(line)&&line[j]!=',';j++);
         if(j<len(line))
         {
            line[j]=0;
            (*callback)(x,y,z,atoi(line.substr(i).c_str()));
         }
      }
   }
   file->close();
   delete file;
   return true;
}
bool readMap(const std::string& filename)
{
   std::string prefix = std::string(MAPCSV_);
   // clear any old map data
   for(int x=0;x<MAPX;x++)
   for(int y=0;y<MAPY;y++)
   for(int z=0;z<MAPZ;z++)
   {
      levelmap[x][y][z].flag=0;
      levelmap[x][y][z].special=SPECIAL_NONE;
      levelmap[x][y][z].siegeflag=0;
   }
   // Try first floor (eg MAPCSV_BANK_TILES_CSV), abort this method if it doesn't exist
   if(!readMapFile(prefix+filename+TILES_CSV, 0, readMapCBTiles)) return false;
   if(!readMapFile(prefix+filename+SPECIALS_CSV, 0, readMapCBSpecials)) return false;
   // Try upper levels (eg MAPCSV_BANK2_TILES_CSV), but don't sweat it if they don't exist
   for(int z=1;z<MAPZ;z++)
   {
      std::string str=tostring(z+1);
      if(!readMapFile(prefix+filename+str+TILES_CSV, z, readMapCBTiles)) break;
      if(!readMapFile(prefix+filename+str+SPECIALS_CSV, z, readMapCBSpecials)) break;
   }
   return true;
}