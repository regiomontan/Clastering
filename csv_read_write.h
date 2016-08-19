
 #ifndef CSV_READ_WRITE_H_INCLUDED
 #define CSV_READ_WRITE_H_INCLUDED

 #include <fstream>
 #include <iostream>
 #include <unordered_set>
 #include "claster.h"
 //-----------------------------------------------------------------
 // ������ csv-�����: ������ ������ -- ���������, ��������� ������
 // �������� ������ (��� ��. �����) � ���� (��� ����������) �����
 // �����, ��������� -- ';'.
 //-----------------------------------------------------------------

 void  write_csv( const std::string                  &filename,
                  const std::unordered_set<cl_point>  &points   );

 void  read_csv( const std::string             &filename,
                 std::unordered_set<cl_point>  &points    );


 #endif // CSV_READ_WRITE_H_INCLUDED
