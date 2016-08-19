
 #include  "csv_read_write.h"
 #include  <sstream>
 #include  <string>
 #include  <iostream>
 #include  <fstream>
 //-----------------------------------------------------------------
 void  write_csv( const std::string                  &filename,
                  const std::unordered_set<cl_point> &points     )
 {
   std::ofstream csv_file( filename, std::ios_base::app );
       if( !csv_file )
	   {
		 std::cerr << "File error" << std::endl;
		 return;
       }
       for ( const auto &p : points )
       {
         csv_file << p.number          << ";";
         csv_file << p.x               << ";";
         csv_file << p.y               << ";";
         csv_file << p.z               << ";";
         csv_file << p.claster_number;
         csv_file << "\n";
       }
   csv_file.close();
 }
 //-----------------------------------------------------------------
 std::istream& operator >> ( std::istream &ins, cl_point &point )
 {
   std::string  line;
   getline( ins, line );
   std::stringstream  ss( line );
   std::string        field;

   getline( ss, field, ';' );
   std::stringstream fn( field );
   size_t  number;
   fn >>   number;

   getline( ss, field, ';' );
   std::stringstream fx( field );
   int  x;
   fx >> x;

   getline( ss, field, ';' );
   std::stringstream fy( field );
   int  y;
   fy >> y;

   getline( ss, field, ';' );
   std::stringstream fz( field );
   int  z;
   fz >> z;

   point = { number, x, y, z, 0 };
   return ins;
 }
 //-----------------------------------------------------------------
 void  read_csv( const std::string            &filename,
                 std::unordered_set<cl_point> &points     )
 {
   std::ifstream csv_file( filename );
       if( !csv_file )
	   {
		 std::cerr << "File error" << std::endl;
		 return;
       }
   std::string  first_str;              // первую строку
   std::getline( csv_file, first_str ); // пропускаю
   cl_point p = { 0, 0, 0, 0, 0 };
       while( 1 )
       {
         csv_file >> p;
             if ( csv_file.eof() )
             break;
         points.insert( p );
       }
   csv_file.close();
 }
//-----------------------------------------------------------------
