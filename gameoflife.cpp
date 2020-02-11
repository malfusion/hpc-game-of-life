
// OpenMP program to print Hello World 
// using C language 
  
// OpenMP header 
#include <omp.h> 
#include <chrono>

#include <stdio.h> 
#include <stdlib.h>
#include <iostream>  
#include <vector> 
#include <random> 
//#include <pair> 
#include <SFML/Graphics.hpp>


using namespace std;

int main(int argc, char* argv[]) 
{ 
  

	int w = 1000;
	int h = 1000;
	
	int arr1[h][w];
	int arr2[h][w];
	
	
	for (int i=0;i<h;i++) {
		for (int j=0;j<w;j++) {
			arr1[i][j] = rand() % 2;
			arr2[i][j] = 0;
		}
	}
	
//	using lifeGrid = int[h][w];
//	lifeGrid *life = &arr1;
//	lifeGrid *lifenext = &arr2;
	
//	cout << *life[0][1] << "ASdasdasdasdasdasasdas\n";

	
	vector< pair <int,int> > neighs;
	neighs.push_back(pair<int, int>(1, 0));
	neighs.push_back(pair<int, int>(1, 1));
	neighs.push_back(pair<int, int>(0, 1));
	neighs.push_back(pair<int, int>(-1, 1));
	neighs.push_back(pair<int, int>(-1, 0));
	neighs.push_back(pair<int, int>(-1, -1));
	neighs.push_back(pair<int, int>(0, -1));
	neighs.push_back(pair<int, int>(1, -1));
	
	
	for (int k=0; k<1; k++){
		// Beginning of parallel region 
		
	}
	
	// create the window
	sf::RenderWindow window(sf::VideoMode(2000, 2000), "My window");
//	window.setFramerateLimit(60);
//	window.SetFramerateLimit(0);
//	window.UseVerticalSync(false);
	sf::CircleShape dot(1.f);
	dot.setFillColor(sf::Color::Yellow);

	const int distance = 4; //distance between dots
	const float offset = distance/2.f; //offset for odd rows
	const float height = 1;//std::sqrt(std::pow(distance,2.f) - std::pow(offset,2.f)); //height of triangles
	cout <<height;
	// run the program as long as the window is open
//	while (window.isOpen())
//	{
//		// check all the window's events that were triggered since the last iteration of the loop
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			// "close requested" event: we close the window
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//		
		chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
		
		// chunksize c
		int iterations = 1000;
		int c = 100;
		for (int k=0; k<iterations; k++){
			#pragma omp parallel for
			for (int n=0; n<h/c; n++){
				for (int i=0;i<c;i++) {
					for (int j=0;j<c;j++) {
						int live = 0;
						vector<pair<int, int> >::iterator neigh;
						for(neigh = neighs.begin(); neigh != neighs.end(); neigh++) {
							int newi = n*c + i + (*neigh).first;
							int newj = n*c + j + (*neigh).second;
			//				if(newi >=0  && newj >=0 && newi < 5 && newj < 5 && *life[newi][newj] == 1){
							if(newi >=0  && newj >=0 && newi < h && newj < w && arr1[newi][newj] == 1){
								live++;
							}
						}
			//			int curr = *life[i][j];
						int curr = arr1[i][j];
			//			cout << *life[0][1] << "ASdasdasdasdasdasasdas\n";
						if (curr == 1){
							if(live < 2){
								curr = 0;
							}
							if(live > 3){
								curr = 0;
							}
						}else{
							if(live == 3){
								curr = 1;
							}
						}
			//			*lifenext[i][j] = curr;
						arr2[i][j] = curr;
					}
				}
			}
			// Ending of parallel region 
			
			for (int i=0;i<h;i++) {
				for (int j=0;j<w;j++) {
					arr1[i][j] = arr2[i][j];
				}
			}
		}
		
		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();		
		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double> >(t2 - t1);
		std::cout << "It took me " << time_span.count() << " seconds.";
		std::cout << "Estimated FPS " << iterations*1/time_span.count() << " seconds.";


		

		// clear the window with black color
//		window.clear(sf::Color::Black);
//
//		// draw everything here...
//		for (int i=0; i<h; ++i){
//			for (int j=0; j<w; ++j){
//				if(arr1[i][j] == 1){
//					dot.setPosition(j*4, i*4); //even rows
//					window.draw(dot);	
//				}
//				
//			}
//		}
//
//		// end the current frame
//		window.display();
//	}

//	return 0;
	
	
} 