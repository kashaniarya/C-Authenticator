// main.cpp
//
// ICS 45C Fall 2018
// Project #3: Maps and Legends

#include "HashMap.hpp"
#include <string>
#include <iostream>



void func_create(HashMap* hm, std::string s2, std::string s1) {
	int curr_sz = hm->size();
	hm->add(s2, s1);
	if(curr_sz == hm->size()) {
		std::cout << "EXISTS" << std::endl;
	}
	else {
		std::cout << "CREATED" << std::endl;
	}
}


void func_login(HashMap* hm, std::string s2, std::string s1) {
	if(hm->contains(s2) and hm->value(s2) == s1) {
		std::cout << "SUCCEEDED" << std::endl;
	}
	else {
		std::cout << "FAILED" << std::endl;
	}
}

void func_for_create_and_login(HashMap* hm, std::string s, std::string word) {
	// GET RID OF ANY WHITE SPACE BEFORE FIRST WORD
	while(s.substr(0,1) == " ") {
		s = s.substr(1, s.length());
	}
	// CHECK TO SEE IF CHECK IS FIRST WORD
	int create_location = s.find(word);
	if(create_location == 0) {
		// REMOVE THE WORD 'CREATE' AND SPACE AFTER IT 
		std::string s1 = s.substr(word.size(), s.length());
		// IF ANYMORE SPACE, REMOVE IT
		while(s1.substr(0,1) == " ") {
			s1 = s1.substr(1, s1.length());
		}
		if (s1.find(" ") != std::string::npos) {
			// FIND NEXT SPACE
			int x = s1.find(" ");
			// STORE USERNAME IN S2
			std::string s2 = s1.substr(0,x);
			// REMOVE USER FROM REST OF STRING
			s1 = s1.substr(x+1, s1.length());
			// REMOVE ANY MORE WHITE SPACE THAT MIGHT BE
			while(s1.substr(0,1) == " ") {
				s1 = s1.substr(1, s1.length());
			}
			// IF ANY WHITESPACE LEFT
			if(s1.find(" ") != std::string::npos) {
				std::string z = s1.substr(s1.length()-1, s1.length());
				if(z == " ") {
					// get rid of all white space at end
					while(z == " ") {
						s1 = s1.substr(0, s1.length()-1);
						z = s1.substr(s1.length()-1, s1.length());
					}
					// check to make sure no white space in middle of pass
					if(s1.find(" ") != std::string::npos) {
						std::cout << "INVALID" << std::endl;
					}
					else if(s1.length() > 0) {
						// user and pass is good
						if(word == "CREATE ") {
							func_create(hm, s2,s1);
						}
						else {
							func_login(hm, s2,s1);
						}
					}
					else {
						std::cout << "INVALID" << std::endl;
					}
				}
				else {
					std::cout << "INVALID" << std::endl;
				}
			}
			else if (s1.length() > 0) {
				//user and pass is ready
				if(word == "CREATE ") {
					func_create(hm, s2,s1);
				}
				else {
					func_login(hm, s2,s1);
				}
			}
			else {
				std::cout << "INVALID" << std::endl;
			}
		}
		else { 
			std::cout << "INVALID" << std::endl;
		}
	}
	// OTHERWISE IT IS INVALID 
	else {
		std::cout << "INVALID" << std::endl;
	}
}





void func_remove(HashMap* hm, std::string s) {
	// GET RID OF ANY WHITE SPACE BEFORE FIRST WORD
	while(s.substr(0,1) == " ") {
		s = s.substr(1, s.length());
	}
	// CHECK TO SEE IF CHECK IS FIRST WORD
	int create_location = s.find("REMOVE ");
	if(create_location == 0) {
		// REMOVE THE WORD 'REMOVE' AND SPACE AFTER IT 
		std::string s1 = s.substr(s.find("REMOVE ")+7, s.length());
		// IF ANYMORE SPACE, REMOVE IT
		while(s1.substr(0,1) == " ") {
			s1 = s1.substr(1, s1.length());
		}
		// if any whitespace left
		if(s1.find(" ") != std::string::npos) {
			std::string z = s1.substr(s1.length()-1, s1.length());
			if(z == " ") {
				// get rid of all white space at end
		 		while(z == " ") {
		 			s1 = s1.substr(0, s1.length()-1);
		 			z = s1.substr(s1.length()-1, s1.length());
		 		}
		 		//if any whitespace then its shitty
		 		if(s1.find(" ") != std::string::npos) {
		 			std::cout << "INVALID" << std::endl;
		 		}
		 		else {
		 			//i have a username
		 			int current_size = hm->size();
		 			hm->remove(s1);
		 			if(current_size == hm->size()) {
		 				std::cout << "NONEXISTENT" << std::endl;
		 			}
		 			else {
		 				std::cout << "REMOVED" << std::endl;
		 			}
		 		}
			}
			else {
				//there is whitespace in middle so shitty
				std::cout << "INVALID" << std::endl;
			}
		}
		else {
			//i have a username
			int current_size = hm->size();
 			hm->remove(s1);
 			if(current_size == hm->size()) {
 				std::cout << "NONEXISTENT" << std::endl;
 			}
 			else {
 				std::cout << "REMOVED" << std::endl;
 			}
		}
	}
	// OTHERWISE IT IS INVALID 
	else {
		std::cout << "INVALID" << std::endl;
	}
}





bool func_debug_off(HashMap* hm, std::string s, std::string word) {
	// GET RID OF ANY WHITE SPACE BEFORE FIRST WORD
	while(s.substr(0,1) == " ") {
		s = s.substr(1, s.length());
	}
	// CHECK TO SEE IF CHECK IS FIRST WORD
	int create_location = s.find(word);
	if(create_location == 0) {
		// REMOVE THE WORD 'REMOVE' AND SPACE AFTER IT 
		std::string s1 = s.substr(word.length(), s.length());
		// IF ANYMORE SPACE, REMOVE IT
		while(s1.substr(0,1) == " ") {
			s1 = s1.substr(1, s1.length());
		}
		//now check if next word is OFF
		if(s1.substr(0,3) == "OFF") {
			//now check everything after OFF
			if(s1.length() > 3) {
				std::string last_s = s1.substr(s1.length()-1, s1.length());
				if(last_s == " ") {
					while(last_s == " ") {
						s1 = s1.substr(0, s1.length()-1);
						last_s = s1.substr(s1.length()-1, s1.length());
					}
					if(s1 == "OFF") {
						std::cout << "OFF NOW" << std::endl;
						return false;
					}
					else {
						std::cout << "INVALID" << std::endl;
					}
				}
				else {
					std::cout << "INVALID" << std::endl;
				}
			}
			else {
				std::cout << "OFF NOW" << std::endl;
				return false;
			}
		}
		else {
			std::cout << "INVALID" << std::endl;
		}

	}
	else {
		std::cout << "INVALID" << std::endl;
	}
	return true;
}


void func_helper(HashMap* hm, std::string ss1, std::string word, std::string word2) {
	// GET RID OF ANY WHITE SPACE BEFORE FIRST WORD
	while(ss1.substr(0,1) == " ") {
		ss1 = ss1.substr(1, ss1.length());
	}
	// CHECK TO SEE IF CHECK IS FIRST WORD
	int create_location = ss1.find(word);
	if(create_location == 0) {
		// REMOVE THE WORD 'REMOVE' AND SPACE AFTER IT 
		std::string s1 = ss1.substr(word.length(), ss1.length());
		// IF ANYMORE SPACE, REMOVE IT
		while(s1.substr(0,1) == " ") {
			s1 = s1.substr(1, s1.length());
		}
		//now check if next word is OFF
		if(s1.substr(0,word2.length()) == word2) {
			//now check everything after OFF
			if(s1.length() > word2.length()) {
				std::string last_s = s1.substr(s1.length()-1, s1.length());
				if(last_s == " ") {
					while(last_s == " ") {
						s1 = s1.substr(0, s1.length()-1);
						last_s = s1.substr(s1.length()-1, s1.length());
					}
					if(s1 == word2) {
						if(word == "LOGIN ") {
							std::cout << hm->size() << std::endl;
						}
						else if (word == "BUCKET ") {
							std::cout << hm->bucketCount() << std::endl;
						}
						else if (word == "LOAD ") {
							std::cout << hm->loadFactor() << std::endl;
						}
						else {
							std::cout << "INVALID" << std::endl;
						}
						
					}
					else {
						std::cout << "INVALID" << std::endl;
					}
				}
				else {
					std::cout << "INVALID" << std::endl;
				}
			}
			else {
				if(word == "LOGIN ") {
					std::cout << hm->size() << std::endl;
				}
				else if (word == "BUCKET ") {
					std::cout << hm->bucketCount() << std::endl;
				}
				else if (word == "LOAD "){
					std::cout << hm->loadFactor() << std::endl;
				}
				else {
					std::cout << "INVALID" << std::endl;
				}
			}
		}
		else {
			std::cout << "INVALID" << std::endl;
		}
	}
	else {
		std::cout << "INVALID" << std::endl;
	}
}





void debug_helper(HashMap* hm) {
	std::cout << "ON NOW" << std::endl;
	bool debugger = true;
	while (debugger) {
		std::string ss1;
		std::getline(std::cin, ss1);

		if(ss1.find("DEBUG ") != std::string::npos and ss1.find("OFF") != std::string::npos) {
			debugger = func_debug_off(hm, ss1, "DEBUG ");
		}
		else if (ss1.find("LOGIN ") != std::string::npos and ss1.find("COUNT") != std::string::npos) {
			func_helper(hm, ss1, "LOGIN ", "COUNT");
		}
		else if (ss1.find("BUCKET ") != std::string::npos and ss1.find("COUNT") != std::string::npos) {
			func_helper(hm, ss1, "BUCKET ", "COUNT");
		}
		else if(ss1.find("LOAD ") != std::string::npos and ss1.find("FACTOR") != std::string::npos) {
			func_helper(hm, ss1, "LOAD ", "FACTOR");
		}

		else if(ss1.find("MAX ") != std::string::npos and ss1.find("BUCKET ") != std::string::npos and ss1.find("SIZE") != std::string::npos) {
			// GET RID OF ANY WHITE SPACE BEFORE FIRST WORD
			while(ss1.substr(0,1) == " ") {
				ss1 = ss1.substr(1, ss1.length());
			}
			// CHECK TO SEE IF CHECK IS FIRST WORD
			int create_location = ss1.find("MAX ");
			if(create_location == 0) {
				// REMOVE THE WORD 'MAX' AND SPACE AFTER IT 
				std::string s1 = ss1.substr(4, ss1.length());
				// IF ANYMORE SPACE, REMOVE IT
				while(s1.substr(0,1) == " ") {
					s1 = s1.substr(1, s1.length());
				}
				//now check if next word is BUCKET
				int create_location2 = s1.find("BUCKET ");
				if(create_location2 == 0) {
					// REMOVE THE WORD 'BUCKET ' AND SPACE AFTER IT 
					s1 = s1.substr(7, s1.length());
					// IF ANYMORE SPACE, REMOVE IT
					while(s1.substr(0,1) == " ") {
						s1 = s1.substr(1, s1.length());
					}
					//now check if word is SIZE
					int create_location3 = s1.find("SIZE");
					if(create_location3 == 0) {
						// left off here
						if(s1.length() > 4) {
							std::string z = s1.substr(s1.length()-1, s1.length());
							if(z == " ") {
								while(z == " ") {
									s1 = s1.substr(0, s1.length()-1);
									z = s1.substr(s1.length()-1, s1.length());
								}
								if(s1.find(" ") != std::string::npos) {
									// found space, error
									std::cout << "INVALID" << std::endl;
								}
								else { 
									//didint find space, max bucket size!
									std::cout << hm->maxBucketSize() << std::endl;
								}
							}
							else {
								std::cout << "INVALID" << std::endl;
							}
						}
						else {
							//max bucket size!
							std::cout << hm->maxBucketSize() << std::endl;
						}

					}
					else {
						std::cout << "INVALID" << std::endl;
					}
				}
				else {
					std::cout << "INVALID" << std::endl;
				}
			}
			else {
				std::cout << "INVALID" << std::endl;
			}
		}
		else if(ss1.find("DEBUG ") != std::string::npos and ss1.find("ON")) {
			//
			while(ss1.substr(0,1) == " ") {
				ss1 = ss1.substr(1, ss1.length());
			}
			// CHECK TO SEE IF CHECK IS FIRST WORD
			int create_location = ss1.find("DEBUG ");
			if(create_location == 0) {
				// REMOVE THE WORD 'REMOVE' AND SPACE AFTER IT 
				std::string s1 = ss1.substr(6, ss1.length());
				// IF ANYMORE SPACE, REMOVE IT
				while(s1.substr(0,1) == " ") {
					s1 = s1.substr(1, s1.length());
				}
				//now check if next word is ON
				if(s1.substr(0,2) == "ON") {
					//now check everything after ON
					if(s1.length() > 2) {
						std::string z = s1.substr(s1.length()-1, s1.length());
						if(z == " ") {
							while(z == " ") {
								s1 = s1.substr(0, s1.length()-1);
								z = s1.substr(s1.length()-1, s1.length());
							}
							if(s1 == "ON") {
								//its good. its DEBUG ON
								std::cout << "ON ALREADY" << std::endl;
							}
							else {
								std::cout << "INVALID" << std::endl;
							}
						}
						else {
							//its good. its DEBUG ON
							std::cout << "INVALID" << std::endl;
						}
					}
					else {
						std::cout << "ON ALREADY" << std::endl;
					}
				}
				else {
					std::cout << "INVALID" << std::endl;
				}
			}
			else {
				std::cout << "INVALID" << std::endl;
			}

		}
		else {
			std::cout << "INVALID" << std::endl;
		}
	}
}





void func_debug_on(HashMap* hm, std::string s) {
	// GET RID OF ANY WHITE SPACE BEFORE FIRST WORD
	while(s.substr(0,1) == " ") {
		s = s.substr(1, s.length());
	}
	// CHECK TO SEE IF CHECK IS FIRST WORD
	int create_location = s.find("DEBUG ");
	if(create_location == 0) {
		// REMOVE THE WORD 'DEBUG ' AND SPACE AFTER IT 
		std::string s1 = s.substr(6, s.length());
		// IF ANYMORE SPACE, REMOVE IT
		while(s1.substr(0,1) == " ") {
			s1 = s1.substr(1, s1.length());
		}
		//now check if next word is ON
		if(s1.substr(0,2) == "ON") {
			//now check everything after ON
			if(s1.length() > 2) {
				std::string z = s1.substr(s1.length()-1, s1.length());
				if(z == " ") {
					while(z == " ") {
						s1 = s1.substr(0, s1.length()-1);
						z = s1.substr(s1.length()-1, s1.length());
					}
					if(s1 == "ON") {
						//its good. its DEBUG ON
						debug_helper(hm);
					}
					else {
						std::cout << "INVALID" << std::endl;
					}
				}
				else {
					//its good. its DEBUG ON
					std::cout << "INVALID" << std::endl;
				}
			}
			else {
				debug_helper(hm);
			}
		}
		else {
			std::cout << "INVALID" << std::endl;
		}
	}
	else {
		std::cout << "INVALID" << std::endl;
	}
}






int main()
{
	HashMap hm;
	bool running = true;
	while(running) {
		std::string s;
		std::getline(std::cin, s);
		if(s == "QUIT") {
			std::cout << "GOODBYE" << std::endl;
			running = false;
		}
		else if(s == "CLEAR") {
			std::cout << "CLEARED" << std::endl;
			hm.clear_and_remove_all();
		}
		else if(s.find("CREATE ") != std::string::npos) {
			func_for_create_and_login(&hm, s, "CREATE ");
		}
		else if(s.find("LOGIN ") != std::string::npos and s.find("COUNT") == std::string::npos) {
			func_for_create_and_login(&hm, s, "LOGIN ");
		}
		else if(s.find("REMOVE ") != std::string::npos) {
			func_remove(&hm,s);
		}
		else if(s.find("DEBUG ") != std::string::npos and s.find("ON") != std::string::npos) {
			func_debug_on(&hm, s);
		}
		else if(s.find("DEBUG ") != std::string::npos and s.find("OFF") != std::string::npos) {	
			//
			// GET RID OF ANY WHITE SPACE BEFORE FIRST WORD
			while(s.substr(0,1) == " ") {
				s = s.substr(1, s.length());
			}
			// CHECK TO SEE IF CHECK IS FIRST WORD
			int create_location = s.find("DEBUG ");
			if(create_location == 0) {
				// REMOVE THE WORD 'REMOVE' AND SPACE AFTER IT 
				std::string s1 = s.substr(6, s.length());
				// IF ANYMORE SPACE, REMOVE IT
				while(s1.substr(0,1) == " ") {
					s1 = s1.substr(1, s1.length());
				}
				//now check if next word is OFF
				if(s1.substr(0,3) == "OFF") {
					//now check everything after OFF
					if(s1.length() > 3) {
						std::string last_s = s1.substr(s1.length()-1, s1.length());
						if(last_s == " ") {
							while(last_s == " ") {
								s1 = s1.substr(0, s1.length()-1);
								last_s = s1.substr(s1.length()-1, s1.length());
							}
							if(s1 == "OFF") {
								std::cout << "OFF ALREADY" << std::endl;
							}
							else {
								std::cout << "INVALID" << std::endl;
							}
						}
						else {
							std::cout << "INVALID" << std::endl;
						}
					}
					else {
						std::cout << "OFF ALREADY" << std::endl;
					}
				}
				else {
					std::cout << "INVALID" << std::endl;
				}

			}
			else {
				std::cout << "INVALID" << std::endl;
			}
		}
		else {
			std::cout << "INVALID" << std::endl;
		}
	}
    return 0;
}



