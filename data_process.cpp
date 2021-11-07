#include "data_process.h"

namespace Arrange {

Person::Person(std::string _name) {
    name = _name;
    for (int i = 1; i < 100; i++) {
        if_available[i] = false;
    }
    for (int i = 1; i <= 7; i++) {
        if_avail_day[i] = true;
    }
}

Data::Data() {
    num_people = 0;
    // update time slice name info
    for (int i = 1; i <= 7; i++) {
        num_time_slice[i] = 8;
        name_time_slice[i][1] = "8:00-10:00";
        name_time_slice[i][2] = "10:00-12:00";
        name_time_slice[i][3] = "12:00-13:30";
        name_time_slice[i][4] = "13:30-15:00";
        name_time_slice[i][5] = "15:00-17:00";
        name_time_slice[i][6] = "17:00-18:30";
        name_time_slice[i][7] = "18:30-20:00";
        name_time_slice[i][8] = "20:00-22:00";
    }
    // cumpute the total number of time slices
    num_time_slice_total = 0;
    for (int i = 1; i <= 7; i++) {
        num_time_slice_total += num_time_slice[i];
    }
}

std::pair<int, int> Data::get_day(int i) {
    std::pair<int, int> result;
    int day = 1;
    do {
        result.first = day;
        result.second = i;
        i -= num_time_slice[day];
        day++;
    } while (i > 0);
    return result;
}

int Data::get_time_slice(int i, int j) {
    int result = 0; 
    for (int day = 1; day < i; day++) {
        result += num_time_slice[day];
    }
    result += j;
    return result;
}

// Data format: a .csv file, the columns represent
//     name, num_time_needed..., if_available..., more_info
void Data::Read(std::string filename) {
    std::ifstream infile(filename);
   	std::string value;
    Person* person = new Person("");
    people.emplace_back(*person);   // Add am empty instance for people[0]
    int index = -5;
    std::getline(infile, value);    // ignore the first title line
    if (infile.is_open()) {
	    while (std::getline(infile, value, index == num_time_slice_total ? '\n' : ',')) {
            index++;
            // read name
            if (index == -4) {
                person = new Person(value);
            }
            // read num_time_need info
            if (index == -3) {
                person->num_time_need["208"] = std::atoi(value.c_str());
            }
            if (index == -2) {
                person->num_time_need["205"] = std::atoi(value.c_str());
                index = 0;
            }
            // read if_available info
            if (index >= 1 && index <= num_time_slice_total && value == "1")
                person->if_available[index] = true;
            // read more info
            if (index == num_time_slice_total + 1) {
                index = -5;
                num_people++;
                people.emplace_back(*person);
            }
        }
	}
}

void Data::Write(std::string filename) {
    std::ofstream oFile;
	oFile.open(filename);
    std::string room_name;
    for (int i = 1; i <= 2; i++) {
        if (i == 1) 
            room_name = "208";
        else
            room_name = "205";
        oFile << room_name << ",周一,周二,周三,周四,周五, ,周六,周日" << std::endl;
        for (int col = 1; col <= 10; col++) {
            if (col <= num_time_slice[1]) {
                oFile << name_time_slice[1][col];
                for (int day = 1; day <= 5; day++) {
                    oFile << "," << get[room_name][this->get_time_slice(day, col)];
                }
            }
            oFile << ",";
            if (col <= num_time_slice[6]) {
                oFile << name_time_slice[6][col];
                for (int day = 6; day <= 7; day++) {
                    oFile << "," << get[room_name][this->get_time_slice(day, col)];
                }
            }
            oFile << std::endl;
        }
    }
    oFile.close();
}

void Data::Write_Statistics(std::string filename) {
    std::ofstream oFile;
	oFile.open(filename);
    oFile << ",208,205,total" << std::endl;
    for (int i = 1; i <= num_people; i++) {
        Person person = people[i];
        int gain = 0;
        oFile << person.name << ",";
        for (int t = 1; t <= num_time_slice_total; t++) {
            if (get["208"][t] == person.name) {
                gain++;
            }
        }
        oFile << gain << ",";
        int _gain = 0;
        for (int t = 1; t <= num_time_slice_total; t++) {
            if (get["205"][t] == person.name) {
                _gain++;
            }
        }
        oFile << _gain << ",";
        oFile << _gain + gain << std::endl;
    }
    oFile.close();
}

} // namespace Arrange