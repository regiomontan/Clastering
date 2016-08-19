
 #include  <iostream>
 #include  "claster.h"
 #include "csv_read_write.h"

 std::unordered_set<cl_point> data_points;
 std::vector<center_point>    claster_centers;
 std::string                  out_filename;
 //------------------------------------------------------------------
 double  distance_from_center( const center_point  &cntr,
                               cl_point             p     )
 {
   double  d_x = cntr.x - p.x;
   double  d_y = cntr.y - p.y;
   double  d_z = cntr.z - p.z;
   return sqrt( d_x*d_x + d_y*d_y + d_z*d_z );
 }
 // ------------------------------------------------------------------
 double  centers_distance( const center_point  &c_1,
                           const center_point  &c_2  )
 {
   double d_x = c_1.x - c_2.x;
   double d_y = c_1.y - c_2.y;
   double d_z = c_1.z - c_2.z;
   return sqrt( d_x*d_x + d_y*d_y + d_z*d_z );
 }
 //------------------------------------------------------------------
 center_point center_of_gravity( std::unordered_set<cl_point> points )
 {
   double  x_mean = 0.0;
   double  y_mean = 0.0;
   double  z_mean = 0.0;
       for( const auto &p : points )
       {
         x_mean += p.x;
         y_mean += p.y;
         z_mean += p.z;
       }
   return { x_mean / points.size(), y_mean / points.size(),
            z_mean / points.size()                          };
 }
 //------------------------------------------------------------------
 bool  intersection( const center_point &p, const double  &radius )
 {
      for ( const auto &cntr : claster_centers )
      {
            if ( centers_distance( cntr, p ) < 2*radius )
            {
              return true;
            }
      }
   return false;
 }
 //------------------------------------------------------------------
 void  difference( std::unordered_set<cl_point> cl_points )
 {
      for( auto const &cl : cl_points )
      {
        data_points.erase( cl );
      }
 }
 //------------------------------------------------------------------
 // return: 1 -- OK; 0 -- ran out of data; -1 -- intersection
 //------------------------------------------------------------------
 int create_claster( claster cl )
 {
   std::unordered_set<cl_point> cl_points;
      while( !intersection( cl.center, cl.radius ) )
      {
            if ( data_points.empty() )
              return 0;
        claster_centers.push_back( cl.center );
            for( const auto p : data_points )
            {
                  // если точка попала в шар, она -- кандидат в кластер:
                  if ( distance_from_center( cl.center, p ) < cl.radius )
                  {
                    cl_point temp  = p;
                    temp.claster_number = cl.number;
                    cl_points.insert( temp );
                  }
             }
        center_point new_center = center_of_gravity( cl_points );
             // если центр тяжести отличен от старого центра:
             if ( cl.center != new_center )
             {
               claster_centers.pop_back();
               cl.center = new_center;
             }
             else // центр стабилизировался -- найден кластер:
             {
               difference( cl_points );
               break;
             }
        cl_points.clear();
      } //while ( !intersection( ...
      for ( const auto &p : cl_points )
      {
        std::cout << p.number << "\t" << p.x << "\t" << p.y << "\t"
                  << "\t" << p.z << "\t"<< p.claster_number << std::endl;
      }
      if ( !cl_points.empty() )
      {
        write_csv( out_filename, cl_points );
        return 1;
      }
   return  -1;
 }
 //------------------------------------------------------------------

