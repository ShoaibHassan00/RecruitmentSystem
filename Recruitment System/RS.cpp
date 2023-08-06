#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <sstream>


// Candidate structure
struct Candidate {
    int candidateId;
    std::string name;
    int age;
    std::string skills;
    int years_of_experience;
    bool employed; // Indicates if the candidate is employed or not
};

// JobPosition structure
struct JobPosition {
    std::string title;
    std::string description;
    std::string required_skills;
    bool job_status; // true if the job is available, false if it's not available
};

// Function to generate a random 4-digit number for candidate ID
int generateRandomCandidateId() {
    return 1000 + (std::rand() % 9000); // Generate a random number between 1000 and 9999
}

// Function to add candidate information
void addCandidateInformation(std::vector<Candidate>& candidates) {
    Candidate newCandidate;
    newCandidate.candidateId = generateRandomCandidateId(); // Generate a random 4-digit candidate ID

    std::cout << "Generated Candidate ID: " << newCandidate.candidateId << '\n';

    std::cout << "Enter candidate name: ";
    std::cin.ignore();
    std::getline(std::cin, newCandidate.name);

    std::cout << "Enter candidate age: ";
    std::cin >> newCandidate.age;

    std::cout << "Enter candidate skills: ";
    std::cin.ignore();
    std::getline(std::cin, newCandidate.skills);

    std::cout << "Enter years of experience: ";
    std::cin >> newCandidate.years_of_experience;

    candidates.push_back(newCandidate);
    std::cout << "Candidate information added successfully!\n";
}

// Function to add job position information
void addJobPositionInformation(std::vector<JobPosition>& jobPositions) {
    JobPosition newJob;

    std::cout << "Enter job title: ";
    std::cin.ignore();
    std::getline(std::cin, newJob.title);

    std::cout << "Enter job description: ";
    std::getline(std::cin, newJob.description);

    std::cout << "Enter required skills: ";
    std::getline(std::cin, newJob.required_skills);

    char jobAvailability;
    std::cout << "Is the job available? (y/n): ";
    std::cin >> jobAvailability;
    newJob.job_status = (jobAvailability == 'y' || jobAvailability == 'Y');

    jobPositions.push_back(newJob);
    std::cout << "Job position information added successfully!\n";
}

// Function to display all candidates
void displayAllCandidates(const std::vector<Candidate>& candidates) {
    if (candidates.empty()) {
        std::cout << "No candidates found.\n";
        return;
    }

    std::cout << "===== Candidates List =====\n";
    for (const auto& candidate : candidates) {
        std::cout << "Candidate ID: " << candidate.candidateId << '\n';
        std::cout << "Name: " << candidate.name << '\n';
        std::cout << "Age: " << candidate.age << '\n';
        std::cout << "Skills: " << candidate.skills << '\n';
        std::cout << "Years of Experience: " << candidate.years_of_experience << '\n';
        std::cout << "Employed: " << (candidate.employed ? "Yes" : "No") << "\n\n";
    }
    std::cout << "===========================\n";
}

// Function to display all job positions
void displayAllJobPositions(const std::vector<JobPosition>& jobPositions) {
    if (jobPositions.empty()) {
        std::cout << "No job positions found.\n";
        return;
    }

    std::cout << "===== Job Positions List =====\n";
    for (const auto& job : jobPositions) {
        std::cout << "Title: " << job.title << '\n';
        std::cout << "Description: " << job.description << '\n';
        std::cout << "Required Skills: " << job.required_skills << '\n';
        std::cout << "Availability: " << (job.job_status ? "Available" : "Not Available") << "\n\n";
    }
    std::cout << "==============================\n";
}

// Function to save candidate data to file
// Function to save candidate data to file (append new candidate to existing file)
void saveCandidatesToFile(const std::vector<Candidate>& candidates) {
    std::ofstream file("candidates.txt", std::ios::app); // Use std::ios::app to open the file in append mode
    if (file.is_open()) {
        const Candidate& newCandidate = candidates.back(); // Get the last candidate (the newly added one)
        file << newCandidate.candidateId << '|'
            << newCandidate.name << '|'
            << newCandidate.age << '|'
            << newCandidate.skills << ';' // Change the delimiter to semicolon
            << newCandidate.years_of_experience << '|'
            << newCandidate.employed << '\n';

        file.close();
    } else {
        std::cout << "Error saving candidates file!\n";
    }
}


// Function to save job position data to file
void saveJobPositionsToFile(const std::vector<JobPosition>& jobPositions) {
    std::ofstream file("job_positions.txt");
    if (file.is_open()) {
        for (const auto& job : jobPositions) {
            file << job.title << ',' << job.description << ',' << job.required_skills << ',' << job.job_status << '\n';
        }
        file.close();
    } else {
        std::cout << "Error saving job positions file!\n";
    }
}

// Function to load candidate data from file
std::vector<Candidate> loadCandidatesFromFile() {
    std::vector<Candidate> candidates;
    std::ifstream file("candidates.txt");
    if (file.is_open()) {
        std::string line;
        int lineNum = 0;
        while (std::getline(file, line)) {
            lineNum++;
            std::stringstream ss(line);
            int candidateId, age, experience;
            std::string name, skills;
            bool employed;
            char comma;

            if (ss >> candidateId >> comma &&
                std::getline(ss, name, '|') &&
                ss >> age >> comma &&
                std::getline(ss, skills, ';') && // Change the delimiter to semicolon
                ss >> experience >> comma &&
                ss >> employed) {
                candidates.push_back({candidateId, name, age, skills, experience, employed});
            } else {
                std::cout << "Error reading candidate data from line " << lineNum << ": " << line << std::endl;
            }



        }
        file.close();
    } else {
        std::cout << "Error opening candidates file!\n";
    }
    return candidates;
}

// Function to load job position data from file
std::vector<JobPosition> loadJobPositionsFromFile() {
    std::vector<JobPosition> jobPositions;
    std::ifstream file("job_positions.txt");
    if (file.is_open()) {
        std::string line;
        int lineNum = 0;
        while (std::getline(file, line)) {
            lineNum++;
            std::stringstream ss(line);
            std::string title, description, skills, jobStatus;
            char comma;
            bool jobAvailability;

            if (std::getline(ss, title, ',') &&
                std::getline(ss, description, ',') &&
                std::getline(ss, skills, ',') &&
                ss >> jobStatus) {

                jobAvailability = (jobStatus == "1");
                jobPositions.push_back({title, description, skills, jobAvailability});
            } else {
                std::cout << "Error reading job position data from line " << lineNum << ": " << line << std::endl;
            }
        }
        file.close();
    } else {
        std::cout << "Error opening job positions file!\n";
    }
    return jobPositions;
}

// Function to assign a job to a candidate using their candidate ID
void assignJobToCandidate(std::vector<Candidate>& candidates, std::vector<JobPosition>& jobPositions) {
    int candidateId, jobIndex;
    std::cout << "Enter candidate ID to assign a job: ";
    std::cin >> candidateId;

    auto candidateIt = std::find_if(candidates.begin(), candidates.end(), [candidateId](const Candidate& candidate) {
        return candidate.candidateId == candidateId;
    });

    if (candidateIt == candidates.end()) {
        std::cout << "Candidate not found with the given ID.\n";
        return;
    }

    // Display open job positions
    std::cout << "===== Open Job Positions =====\n";
    for (size_t i = 0; i < jobPositions.size(); ++i) {
        if (jobPositions[i].job_status) {
            std::cout << i << ". " << jobPositions[i].title << '\n';
        }
    }
    std::cout << "==============================\n";

    // Select a job position to assign
    std::cout << "Enter the index of the job position to assign: ";
    std::cin >> jobIndex;

    if (jobIndex >= 0 && jobIndex < jobPositions.size() && jobPositions[jobIndex].job_status) {
        // Assign the job to the candidate
        jobPositions[jobIndex].job_status = false;

        // Update the employed status of the candidate
        candidateIt->employed = true;

        std::cout << "Job \"" << jobPositions[jobIndex].title << "\" has been assigned to candidate with ID " << candidateId << ".\n";
    } else {
        std::cout << "Invalid job index or the selected job is not available for assignment.\n";
    }
}

// Function to delete a candidate by ID
void deleteCandidateById(std::vector<Candidate>& candidates) {
    int candidateId;
    std::cout << "Enter the candidate ID to delete: ";
    std::cin >> candidateId;

    auto candidateIt = std::find_if(candidates.begin(), candidates.end(), [candidateId](const Candidate& candidate) {
        return candidate.candidateId == candidateId;
    });

    if (candidateIt != candidates.end()) {
        candidates.erase(candidateIt);
        std::cout << "Candidate with ID " << candidateId << " has been deleted.\n";

        // Update the "candidates.txt" file after deleting the candidate
        std::ofstream file("candidates.txt");
        if (file.is_open()) {
            for (const auto& candidate : candidates) {
                file << candidate.candidateId << '|'
                     << candidate.name << '|'
                     << candidate.age << '|'
                     << candidate.skills << '|'
                     << candidate.years_of_experience << '|'
                     << candidate.employed << '\n';
            }
            file.close();
        } else {
            std::cout << "Error saving candidates file!\n";
        }
    } else {
        std::cout << "Candidate not found with the given ID.\n";
    }
}



// Function to search candidates by skills
void searchCandidatesBySkills(const std::vector<Candidate>& candidates) {
    std::string searchSkills;
    std::cout << "Enter the skill to search for candidates: ";
    std::cin.ignore();
    std::getline(std::cin, searchSkills);

    // Convert the searchSkills to lowercase to perform a case-insensitive search
    std::transform(searchSkills.begin(), searchSkills.end(), searchSkills.begin(), ::tolower);

    std::vector<Candidate> matchingCandidates;

    for (const auto& candidate : candidates) {
        // Convert the candidate's skills to lowercase for case-insensitive comparison
        std::string candidateSkills = candidate.skills;
        std::transform(candidateSkills.begin(), candidateSkills.end(), candidateSkills.begin(), ::tolower);

        // Check if the candidate's skills contain the searched skill
        if (candidateSkills.find(searchSkills) != std::string::npos) {
            matchingCandidates.push_back(candidate);
        }
    }

    if (!matchingCandidates.empty()) {
        std::cout << "===== Matching Candidates =====\n";
        for (const auto& candidate : matchingCandidates) {
            std::cout << "Candidate ID: " << candidate.candidateId << '\n';
            std::cout << "Name: " << candidate.name << '\n';
            std::cout << "Age: " << candidate.age << '\n';
            std::cout << "Skills: " << candidate.skills << '\n';
            std::cout << "Years of Experience: " << candidate.years_of_experience << '\n';
            std::cout << "Employed: " << (candidate.employed ? "Yes" : "No") << "\n\n";
        }
        std::cout << "==============================\n";
    } else {
        std::cout << "No candidates found with the given skill.\n";
    }
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(0))); // Seed the random number generator with current time

    // Load data from files into vectors (if available)
    std::vector<Candidate> candidates = loadCandidatesFromFile();
    std::vector<JobPosition> jobPositions = loadJobPositionsFromFile();

    int choice;
    do {
        // Display menu options to the user
        std::cout << "========== MENU ==========\n";
        std::cout << "1. Add Candidate\n";
        std::cout << "2. Add Job Position\n";
        std::cout << "3. Display All Candidates\n";
        std::cout << "4. Display All Job Positions\n";
        std::cout << "5. Assign Job to Candidate\n";
        std::cout << "6. Delete Candidate by ID\n";
        std::cout << "7. Search Candidates by Skills\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice (1/2/3/4/5/6/7/8): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addCandidateInformation(candidates);
                saveCandidatesToFile(candidates);
                break;
            case 2:
                addJobPositionInformation(jobPositions);
                saveJobPositionsToFile(jobPositions);
                break;
            case 3:
                displayAllCandidates(candidates);
                break;
            case 4:
                displayAllJobPositions(jobPositions);
                break;
            case 5:
                assignJobToCandidate(candidates, jobPositions);
                saveCandidatesToFile(candidates);
                saveJobPositionsToFile(jobPositions);
                break;
            case 6:
                deleteCandidateById(candidates);
                break;
            case 7:
                searchCandidatesBySkills(candidates);
                break;
            case 8:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

        std::cin.ignore(); // Ignore the leftover newline character from previous input
        std::cout << "Press Enter to continue...";
        std::cin.get(); // Wait for the user to press Enter before displaying the menu again

    } while (choice != 8);

    return 0;
}
