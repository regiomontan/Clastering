
 #ifndef CSV_READ_WRITE_H_INCLUDED
 #define CSV_READ_WRITE_H_INCLUDED

 #include <fstream>
 #include <iostream>
 #include <unordered_set>
 #include "claster.h"
 //-----------------------------------------------------------------
 // Формат csv-файла: первая строка -- заголовок, остальные строки
 // содержат четыре (для вх. файла) и пять (для результата) целых
 // чисел, сепаратор -- ';'.
 //-----------------------------------------------------------------

 void  write_csv( const std::string                  &filename,
                  const std::unordered_set<cl_point>  &points   );

 void  read_csv( const std::string             &filename,
                 std::unordered_set<cl_point>  &points    );


 #endif // CSV_READ_WRITE_H_INCLUDED
