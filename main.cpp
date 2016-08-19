
 /********************************************************************
  Решение тестовой задачи. В трехмерном пространстве, ограниченном
  ____________________     кубом с центром в точке (0; 0; 0) и
  \_______________   /\    длиной стороны 2000 (т.е. максимально воз-
   \_____________/  / /    можная координата в этом пространстве
     ______     /  /_/     +- 1000) сгенерированы K сфер, объем кото-
     \_    /\  /__   /\    рых равномерно заполнен N = 10 000 точек.
      \/  / /  \ /  / /    Задача – по имеющимся координатам точек вы-
      /  / /    /  / /     делить эти K сфер и присвоить каждой точке
     /  /_/___ /  / /      номер сферы, к которой она относится.
    /___________ / /       Входные данные: .csv файл, в котором указаны
    \____________\/        номера точек, три координаты.
                           Результат: .csv файл, в котором указаны но-
  мера точек, три координаты и номер кластера, к которому принадлежит
  каждая точка. Вариант 1: радиус сфер R одинаковый и равен 250. Центры
  сфер находятся на расстоянии не меньше чем 2R.
  Copyright: В.Зенкин, 2016 (v_zenk@mail.ru).
 *********************************************************************/
 #include  <iostream>
 #include  <unordered_set>
 #include  <vector>
 #include  <random>
 #include  <ctime>
 #include  <stdlib.h>     /* atoi */
 #include  "claster.h"
 #include  "csv_read_write.h"
 //--------------------------------------------------------------------
 int  main( int argc, char *argv[] )
 {
   //===================================================================
   const double  radius     = 250;
   int number_of_iterations = 0;
   //===================================================================
       if ( argc != 2 )
       {
         std::cout << "Usage: claster3D.exe number_of_iterations" \
                   << std::endl;
         std::cin.get();
         return 0;
       }
       else
         number_of_iterations = atoi( argv[1] );
   read_csv( "task.csv", data_points );
   out_filename = "clustered_data.csv";     // подготовка файла
   std::ofstream csv_file( out_filename );  // для результатов
       if( !csv_file )
	   {
		 std::cerr << "File error" << std::endl;
		 return 1;
       }
   csv_file << "Point Number" << ";";
   csv_file << "X cooridnate" << ";";
   csv_file << "Y coordinate" << ";";
   csv_file << "Z coordinate"   << ";";
   csv_file << "Claster number";
   csv_file << "\n";
   csv_file.close();

   std::cout << "processing... " << std::endl;
   srand( time( 0 ) );
   size_t claster_number = 1;
       for ( size_t iter = 1; iter <= number_of_iterations; ++iter )
       {
         auto rand_point = data_points.begin();
         std::advance( rand_point, rand() % data_points.size() );
         center_point center = { static_cast<double>(rand_point->x),
                                 static_cast<double>(rand_point->y),
                                 static_cast<double>(rand_point->z)  };
         std::cout << "-- iterations # " << iter << " -------------\n";
         int res = create_claster( { radius, center, claster_number } );
             if ( res == 0 )  break;
             if ( res == 1 )  ++claster_number;
       }
   std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
   std::cout << "claster_centers = \n";
   std::ofstream  cl_cntr_file( "claster_centers.txt" );
       for ( const auto &c : claster_centers )
       {
         cl_cntr_file << c.x << " "  << c.y << " " << c.z << "\n";
         std::cout    << c.x << ", " << c.y << ", " << c.z << std::endl;
       }
   cl_cntr_file.close();
   std::cout << "\n";
   std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
   std::cout << "The rest: \n";
       for ( const auto &p : data_points )
       {
         std::cout << p.number << "\t" << p.x << " " << p.y << "\t"
                   << "\t" << p.z << "\t" << p.claster_number
                   << std::endl;
       }
       if ( !data_points.empty() )
       write_csv( out_filename, data_points );
   std::cout << "The data in the file " << out_filename << ". Press Enter.";
   std::cin.get();
   return 0;
 }
//--------------------------------------------------------------------

