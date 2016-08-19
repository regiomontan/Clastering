
 #ifndef CLASTER_H_INCLUDED
 #define CLASTER_H_INCLUDED

 #include <unordered_set>
 #include <vector>
 #include <cmath>
 //------------------------------------------------------------------
 struct cl_point
 {
   size_t  number;
   int     x;
   int     y;
   int     z;
   size_t  claster_number;
   cl_point( const size_t &number,
             const int    &x,
             const int    &y,
             const int    &z,
              size_t claster_number
            )
            : number         ( number         ),
              x              ( x              ),
              y              ( y              ),
              z              ( z              ),
              claster_number ( claster_number )
   {
   }
   bool operator == (const cl_point &other ) const
   {
     return ( ( x == other.x ) && ( y == other.y ) && ( z == other.z ) );
   }
 };
 //------------------------------------------------------------------
 namespace std
 {
   template <>
   struct hash<cl_point>
   {
      size_t operator () ( const cl_point &p ) const
      {
        return (    (hash<int>()(p.x)
                  ^ (hash<int>()(p.y) << 1)) >> 1 )
                  ^ (hash<int>()(p.z) << 1 );
      }
    };
 }
 //------------------------------------------------------------------
 struct center_point
 {
   double  x;
   double  y;
   double  z;
   bool operator != (const center_point &other ) const
   {
     return  sqrt(   (x - other.x)*(x - other.x)
                   + (y - other.y)*(y - other.y)
                   + (z - other.z)*(z - other.z)  ) > 0.05;
   }
 };
 //------------------------------------------------------------------
 struct claster
 {
   const double  radius;
   center_point  center;
   size_t        number;
 };
 //===================================================================
 extern std::vector<center_point>    claster_centers;// данные
 extern std::unordered_set<cl_point> data_points;    // центры кластеров
 extern std::string                  out_filename;   // файл результатов
 //===================================================================
 int  create_claster( claster cl );

 #endif // CLASTER_H_INCLUDED
