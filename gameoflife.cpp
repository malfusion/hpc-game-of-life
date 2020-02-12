
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
  
	int h = 1000;
	int w = 1000;
	
	int arr1[h+2][w+2];
	int arr2[h+2][w+2];
	
	
	for (int i=0;i<h+2;i++) {
		for (int j=0;j<w+2;j++) {
			if(i==0 || j==0 || i==h+1 || j==w+1) {
				arr1[i][j] = 0;
				arr2[i][j] = 0;
			}
			else{
				arr1[i][j] = rand() % 2;
				arr2[i][j] = 0;		
			}
		}
	}
	
//	using lifeGrid = int[h][w];
//	lifeGrid *life = &arr1;
//	lifeGrid *lifenext = &arr2;
	
	// create the window
	sf::RenderWindow window(sf::VideoMode(2000, 2000), "My window");
	sf::CircleShape dot(2.f, 4);
	dot.setFillColor(sf::Color::Yellow);

	const int distance = 4;
	const float offset = distance/2.f;
	const float height = 1;

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
//		chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
		
		// chunksize c
		int iterations = 1000;
		int c = 20;
		for (int k=0; k<iterations; k++){
			#pragma omp parallel for
			for (int ni=0; ni<floor(h/c); ni++){
//				for (int nj=0; nj<floor(w/c); nj++){
					for (int i=0;i<c;i++) {
						for (int j=0;j<w;j++) {
							int ci = ni*c + i + 1;
							int cj = j+1;
							int live = arr1[ci+1][cj] + arr1[ci+1][cj+1] + arr1[ci][cj+1] + arr1[ci-1][cj+1] + arr1[ci-1][cj] + arr1[ci-1][cj-1] + arr1[ci][cj-1] + arr1[ci+1][cj-1];
	//						cout << live;
				//			int curr = *life[i][j];
							int curr = arr1[ci][cj];
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
							arr2[ci][cj] = curr;
						}
					}
//				}
			}
			// Ending of parallel region 
			window.clear(sf::Color::Black);

			// draw everything here...
			for (int i=0; i<h+2; ++i){
				for (int j=0; j<w+2; ++j){
					if(arr2[i][j] == 1){
						dot.setFillColor(arr1[i][j] == 1 ? sf::Color::Yellow : sf::Color::Green);
						dot.setPosition(i*4, j*4); //even rows
						window.draw(dot);	
					}
					
				}
			}

			// end the current frame
			window.display();
			
			
			for (int i=0;i<h+2;i++) {
				for (int j=0;j<w+2;j++) {
					arr1[i][j] = arr2[i][j];
				}
			}
		}
		
//		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();		
//		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double> >(t2 - t1);
//		std::cout << "It took me " << time_span.count() << " seconds.";
//		std::cout << "Estimated FPS " << iterations*1/time_span.count();
		
	}
	
} 