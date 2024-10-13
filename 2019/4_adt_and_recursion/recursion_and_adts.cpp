#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#define assertm(exp, msg) assert(((void)msg, exp))

std::vector<std::string> split(std::string s, std::string delimiter) {
  std::vector<std::string> tokens;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    tokens.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  tokens.push_back(s);

  return tokens;
}

void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
}

void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

struct Doctor {
  std::string name;
  int hours_free;
};

struct Patient {
  std::string name;
  int hours_needed;
};

bool no_hours_needed(const std::vector<Patient> &patients) {
  for (auto patient : patients) {
    if (patient.hours_needed > 0) {
      return false;
    }
  }
  return true;
}

bool can_all_patients_be_seen(
    std::vector<Doctor> &doctors, std::vector<Patient> &patients,
    std::map<std::string, std::set<std::string>> &schedule) {

  if (no_hours_needed(patients)) {
    return true;
  }

  for (auto &doctor : doctors) {
    if (doctor.hours_free == 0) {
      continue;
    }

    for (auto &patient : patients) {
      if (patient.hours_needed == 0) {
        continue;
      }

      if (doctor.hours_free >= patient.hours_needed) {
        int temp_doctor_hours_free = doctor.hours_free;
        int temp_patient_hours_needed = patient.hours_needed;

        doctor.hours_free = doctor.hours_free - patient.hours_needed;
        patient.hours_needed = 0;

        schedule[doctor.name].insert(patient.name);

        if (can_all_patients_be_seen(doctors, patients, schedule)) {
          return true;
        }

        doctor.hours_free = temp_doctor_hours_free;
        patient.hours_needed = temp_patient_hours_needed;

        schedule[doctor.name].erase(patient.name);
      }
    }
  }

  return false;
}

void test_doctors_without_orders() {
  std::string test_cases_path = "./resources/DoctorsWithoutOrders";

  for (const auto &entry :
       std::filesystem::directory_iterator(test_cases_path)) {

    std::string line;
    std::ifstream test_file(entry.path());

    // too slow
    if (!entry.path().compare(
            "./resources/DoctorsWithoutOrders/TooManyEvens.dwo")) {
      continue;
    }

    std::cout << std::endl << "Testing file: " << entry.path() << std::endl;

    if (test_file.is_open()) {

      std::vector<Doctor> doctors;
      std::vector<Patient> patients;
      std::map<std::string, std::set<std::string>> schedule;

      bool answer;

      while (std::getline(test_file, line)) {
        if (line[0] == '#') {
          continue;
        }

        size_t columnpos = line.find(":");
        if (columnpos != std::string::npos) {
          std::string label = line.substr(0, columnpos);
          std::string value = line.substr(columnpos + 1);

          std::cout << label << " =" << value << std::endl;

          if (label.find("Doctor") != std::string::npos) {
            doctors.push_back({label, std::stoi(value)});
          }

          if (label.find("Patient") != std::string::npos) {
            patients.push_back({label, std::stoi(value)});
          }

          if (label.find("Answer") != std::string::npos) {
            if (value.find("true") != std::string::npos) {
              answer = true;
            } else {
              answer = false;
            }
          }
        }
      }

      std::string test_case = "";
      test_case += "Testing file: " + entry.path().string() +
                   "it should return " + (answer ? "true" : "false");

      bool result = can_all_patients_be_seen(doctors, patients, schedule);
      assertm(result == answer, test_case);
    }
    test_file.close();
  }
}

using RoadNetworkMapPair = std::pair<std::string, std::set<std::string>>;
using RoadNetworkMap = std::map<std::string, std::set<std::string>>;
using LocationsSet = std::set<std::string>;

void print_road(const RoadNetworkMap &road_network) {
  std::cout << "===" << std::endl;
  for (auto const &[city_src, cities] : road_network) {
    std::cout << city_src << " = ";
    for (auto const &city_dst : cities) {
      std::cout << city_dst << ",";
    }
    std::cout << std::endl;
  }
}

bool _can_be_made_disaster_ready(RoadNetworkMap &road_network, int num_cities,
                                 LocationsSet &locations) {

  if (num_cities == 0 && road_network.size() > 0) {
    return false;
  }

  if (num_cities >= 0 && road_network.size() == 0) {
    // all cities covered
    return true;
  }

  RoadNetworkMap road_network_copy = road_network;
  for (auto [city_src, cities_dst] : road_network_copy) {
    // pick current city
    road_network.erase(city_src);
    if (_can_be_made_disaster_ready(road_network, num_cities - 1, locations)) {
      return true;
    }
    // undo current city
    road_network.insert(RoadNetworkMapPair(city_src, cities_dst));

    for (std::string city_dst : cities_dst) {

      if (road_network.find(city_dst) == road_network.end()) {
        // city not found
        continue;
      }

      std::set<std::string> cities_temp = road_network.find(city_dst)->second;
      road_network.erase(city_dst);
      if (_can_be_made_disaster_ready(road_network, num_cities - 1,
                                      locations)) {
        return true;
      }
      road_network.insert(RoadNetworkMapPair(city_dst, cities_temp));
    }
  }

  return false;
}

bool can_be_made_disaster_ready(
    std::map<std::string, std::set<std::string>> road_network, int num_cities,
    std::set<std::string> &locations) {
  return _can_be_made_disaster_ready(road_network, num_cities, locations);
}

void test_disaster_preparation() {
  std::string test_cases_path = "./resources/DisasterPlanning";

  for (const auto &entry :
       std::filesystem::directory_iterator(test_cases_path)) {

    std::string line;
    std::ifstream test_file(entry.path());

    // too slow
    if (entry.path().string().find("Hard") != std::string::npos) {
      continue;
    }

    std::cout << std::endl << "Testing file: " << entry.path() << std::endl;

    RoadNetworkMap road_network;
    LocationsSet locations;

    if (test_file.is_open()) {

      int solution;

      while (std::getline(test_file, line)) {
        if (line[0] == '#') {
          continue;
        }

        std::vector<std::string> strs = split(line, ":");
        if (strs.size() == 2) {
          std::string key = strs[0];
          std::string values = strs[1];

          if (key.find("Solution") != std::string::npos) {
            solution = std::stoi(values);
            continue;
          }

          std::string city_src = key;
          size_t start_coord = city_src.find("(");
          city_src.erase(start_coord);
          trim(city_src);

          std::set<std::string> cities_set{};
          std::vector<std::string> cities = split(values, ",");
          for (auto city_dst : cities) {
            trim(city_dst);
            cities_set.insert(city_dst);
          }
          road_network.insert(std::pair<std::string, std::set<std::string>>(
              city_src, cities_set));
        }
      }

      std::cout << "solution = " << solution << std::endl;
      std::cout << can_be_made_disaster_ready(road_network, solution + 1,
                                              locations)
                << std::endl;

      std::string test_case = "";
      test_case += "Testing file: " + entry.path().string() +
                   "it should return " + std::to_string(solution);

      // std::cout << test_case << std::endl;
      // assertm(result == answer, test_case);
    }
    test_file.close();
    break;
  }
}

int main() {
  // test_doctors_without_orders();
  test_disaster_preparation();

  return 0;
}
