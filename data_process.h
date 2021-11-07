#ifndef DATA_PROCESS_H_
#define DATA_PROCESS_H_

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

namespace Arrange {

class Person {
  public:
    Person(std::string);
    std::string name;                           // The name of person
    std::map<std::string, int> num_time_need;   // Then number of time slices needed, string stands for "2-08", etc.
    bool if_available[100];                     // Stands for if available in time slice #t
    bool if_avail_day[8];                       // Stands for if available in that day
};

class Data {
  public:
    Data();
    std::pair<int, int> get_day(int);                       // Get the day # and slice # info
    int get_time_slice(int, int);                           // Get the index of time slice given day #i and slice #j
    void Read(std::string);                                 // Read the data from the .csv file
    void Write(std::string);                                // Write the arranged sheet into .csv file
    void Write_Statistics(std::string);                     // Write the statistic of everybody's gain
    int num_people;                                         // Total number of people
    std::vector<Person> people;                             // The vector storing person data
    int num_time_slice_total;                               // The number of time slices totally
    int num_time_slice[8];                                  // The number of time slices each day
    std::string name_time_slice[8][10];                     // The name of time slices each day, e.g. "8:00-10:00"
    std::map<std::string, std::map<int, std::string>> get;  // Store the person name that gets the time slice #t
};

} // namespace Arrange

#endif // DATA_PROCESS_H_