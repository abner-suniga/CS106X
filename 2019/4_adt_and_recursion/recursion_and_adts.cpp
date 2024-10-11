#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <vector>

struct Doctor {
  std::string name;
  int hoursFree;
};

struct Patient {
  std::string name;
  int hoursNeeded;
};

bool noHoursNeeded(const std::vector<Patient> &patients) {
  for (auto patient : patients) {
    if (patient.hoursNeeded > 0) {
      return false;
    }
  }
  return true;
}

bool canAllPatientsBeSeen(
    std::vector<Doctor> &doctors, std::vector<Patient> &patients,
    std::map<std::string, std::set<std::string>> &schedule) {

  if (noHoursNeeded(patients)) {
    return true;
  }

  for (auto &doctor : doctors) {
    if (doctor.hoursFree == 0) {
      continue;
    }

    for (auto &patient : patients) {
      if (patient.hoursNeeded == 0) {
        continue;
      }

      if (doctor.hoursFree >= patient.hoursNeeded) {
        int tempDoctorHoursFree = doctor.hoursFree;
        int tempPatientHoursNeeded = patient.hoursNeeded;

        doctor.hoursFree = doctor.hoursFree - patient.hoursNeeded;
        patient.hoursNeeded = 0;

        schedule[doctor.name].insert(patient.name);

        if (canAllPatientsBeSeen(doctors, patients, schedule)) {
          return true;
        }

        doctor.hoursFree = tempDoctorHoursFree;
        patient.hoursNeeded = tempPatientHoursNeeded;

        schedule[doctor.name].erase(patient.name);
      }
    }
  }

  return false;
}

int main() {

  std::vector<Doctor> doctors{{"Doctor Thomas", 10},
                              {"Doctor Taussig", 8},
                              {"Doctor Sacks", 8},
                              {"Doctor Ofri", 8}};

  std::vector<Patient> patients{
      {"Patient Lacks", 2},      {"Patient Gage", 3},
      {"Patient Molaison", 4},   {"Patient Writebol", 3},
      {"Patient St. Martin", 1}, {"Patient Washkansky", 7},
      {"Patient Sandoval", 8},   {"Patient Giese", 6},
  };

  std::map<std::string, std::set<std::string>> schedule;

  std::cout << (canAllPatientsBeSeen(doctors, patients, schedule) ? "true"
                                                                  : "false")
            << std::endl;

  for (auto pair : schedule) {
    std::cout << pair.first << ": ";
    for (auto patient : pair.second) {
      std::cout << patient << ", ";
    }
    std::cout << std::endl;
  }

  return 0;
}
